/*
    Copyright (C) 2018 Aseman Team
    http://aseman.co

    TelegramStats is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TelegramStats is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stserversorter.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QPointer>

class STServerSorter::Private
{
public:
    QNetworkAccessManager *manager;
    STServerList *list;
    qint32 limit;

    QString error;
    QHash<QNetworkReply*, QByteArray> buffers;

    QList<STServerSorterItem> items;
    QMap<qreal, STServerSorterItem> latencyCache;

    QList<STServerSorterItem> sortByDistance() {
        QMultiMap<qreal, STServerSorterItem> mapCache;
        for(qint32 i=0; i<list->count(); i++)
        {
            STServerSorterItem item = list->item(i);
            if(mapCache.count() < limit)
                mapCache.insertMulti(item.distance(), item);
            else
            if(mapCache.lastKey() > item.distance())
            {
                mapCache.remove(mapCache.lastKey(), mapCache.last());
                mapCache.insertMulti(item.distance(), item);
            }
        }

        return mapCache.values();
    }

    QPointer<QNetworkReply> reply;
};

STServerSorter::STServerSorter(STServerList *list, QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->list = list;
    p->limit = 20;
    p->manager = new QNetworkAccessManager(this);
}

void STServerSorter::setLimit(qint32 limit)
{
    if(p->limit == limit)
        return;

    p->limit = limit;
    Q_EMIT limitChanged();
}

qint32 STServerSorter::limit() const
{
    return p->limit;
}

qint32 STServerSorter::count()
{
    return p->items.count();
}

STServerSorterItem STServerSorter::item(qint32 idx)
{
    return p->items.at(idx);
}

QString STServerSorter::error() const
{
    return p->error;
}

void STServerSorter::setError(const QString &error)
{
    if(p->error == error)
        return;

    p->error = error;
    Q_EMIT errorChanged();
}

void STServerSorter::sortByLatency(qint32 timeout)
{
    if(p->reply)
        return;

    p->latencyCache.clear();
    QList<STServerSorterItem> items = p->sortByDistance();
    startCheckingLatencies(items, items.length(), timeout);
}

void STServerSorter::sortByDistance()
{
    p->items = p->sortByDistance();
    Q_EMIT changed();
}

void STServerSorter::startCheckingLatencies(QList<STServerSorterItem> servers, qint32 total, qint32 timeout)
{
    Q_EMIT latencyProgress(p->latencyCache.count(), total);
    if(servers.isEmpty())
    {
        p->items = p->latencyCache.values();
        p->latencyCache.clear();
        Q_EMIT changed();
        return;
    }

    STServerItem u = servers.takeFirst();

    QNetworkRequest req;
    req.setHeader(QNetworkRequest::UserAgentHeader, p->list->client()->userAgent());
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    req.setUrl(u.latencyUrl());

    QDateTime startTime = QDateTime::currentDateTime();
    p->reply = p->manager->get(req);

    connect(p->reply, &QNetworkReply::readyRead, this, [this](){
        p->buffers[p->reply] += p->reply->readAll();
    });
    connect(p->reply, &QNetworkReply::finished, this, [this, startTime, u, servers, total, timeout](){
        p->reply->deleteLater();
        QByteArray data = p->buffers.take(p->reply);
        STServerSorterItem unit = u;
        if(data.trimmed() == "test=test")
            unit.setLatency( startTime.msecsTo(QDateTime::currentDateTime()) );
        else
            unit.setLatency(INT_MAX);

        p->latencyCache.insertMulti(unit.latency(), unit);
        startCheckingLatencies(servers, total, timeout);
    });

    QTimer *timer = new QTimer(p->reply);
    timer->setInterval(timeout);
    timer->setSingleShot(true);
    timer->connect(timer, &QTimer::timeout, p->reply, &QNetworkReply::abort);
    timer->start();
}

STServerSorter::~STServerSorter()
{
    delete p;
}
