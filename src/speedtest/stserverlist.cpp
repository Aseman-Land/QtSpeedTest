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

#include "stserverlist.h"

#include <QDomDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtMath>

class STServerList::Private
{
public:
    QList<STServerItem> items;
    STClient *client;
    QNetworkAccessManager *manager;

    QString error;
    QByteArray buffer;
    QNetworkReply *reply;
    QString serversUrl;
    bool fetched;

    static qreal measure(qreal lat1, qreal lon1, qreal lat2, qreal lon2){  // generally used geo measurement function
        qreal R = 6378.137; // Radius of earth in KM
        qreal dLat = lat2 * M_PI / 180 - lat1 * M_PI / 180;
        qreal dLon = lon2 * M_PI / 180 - lon1 * M_PI / 180;
        qreal a = qSin(dLat/2) * qSin(dLat/2) +
        qCos(lat1 * M_PI / 180) * qCos(lat2 * M_PI / 180) *
        qSin(dLon/2) * qSin(dLon/2);
        qreal c = 2 * qAtan2(qSqrt(a), qSqrt(1-a));
        qreal d = R * c;
        return d; // meters
    }
};

STServerList::STServerList(STClient *client, QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->fetched = false;
    p->client = client;
    p->serversUrl = QStringLiteral("https://www.speedtest.net/speedtest-servers-static.php");

    p->manager = new QNetworkAccessManager(this);
    p->reply = Q_NULLPTR;
}

qint32 STServerList::count() const
{
    return p->items.count();
}

STServerItem STServerList::item(qint32 idx) const
{
    return p->items.at(idx);
}

void STServerList::setServersUrl(const QString &serversUrl)
{
    if(p->serversUrl == serversUrl)
        return;

    p->serversUrl = serversUrl;
    Q_EMIT serversUrlChanged();
}

QString STServerList::serversUrl() const
{
    return p->serversUrl;
}

QString STServerList::error() const
{
    return p->error;
}

STClient *STServerList::client() const
{
    return p->client;
}

void STServerList::setList(const QList<STServerItem> &items)
{
    p->items = items;
    p->fetched = false;
    Q_EMIT changed();
}

bool STServerList::fetched() const
{
    return p->fetched;
}

void STServerList::setError(const QString &error)
{
    if(p->error == error)
        return;

    p->error = error;
    Q_EMIT errorChanged();
}

void STServerList::fetch()
{
    if(p->reply)
        return;

    p->items.clear();

    QNetworkRequest req;
    req.setHeader(QNetworkRequest::UserAgentHeader, p->client->userAgent());
    req.setUrl( QUrl(p->serversUrl) );

    p->reply = p->manager->get(req);
    connect(p->reply, &QNetworkReply::readyRead, this, [this](){
        p->buffer += p->reply->readAll();
    });
    connect(p->reply, &QNetworkReply::downloadProgress, this, [this](qint64 bytesReceived, qint64 bytesTotal){
        Q_EMIT downloadProgress(bytesReceived, bytesTotal);
    });
    connect(p->reply, &QNetworkReply::finished, this, [this](){
        p->reply->deleteLater();
        p->reply = Q_NULLPTR;
        analizeData();
    });
    connect(p->reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [this](QNetworkReply::NetworkError){
        setError(QStringLiteral("Server file error: ") + p->reply->errorString());
    });
}

void STServerList::analizeData()
{
    QDomDocument doc;
    QString errorMsg;
    if(!doc.setContent(p->buffer, &errorMsg))
    {
        setError(QStringLiteral("Servers file error: ") + errorMsg);
        return;
    }

    qreal clat = p->client->clientConfig().latitude();
    qreal clon = p->client->clientConfig().longitude();

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    n = n.firstChild();

    p->items.clear();

    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            QDomNamedNodeMap attrs = e.attributes();
            QVariantMap attrsMap;
            for(int i=0; i<attrs.length(); i++)
            {
                QDomNode node = attrs.item(i);
                attrsMap[ node.nodeName() ] = node.nodeValue();
            }

            STServerItem item;
            item.setLatitude(attrsMap.value(QStringLiteral("lat")).toDouble());
            item.setLongitude(attrsMap.value(QStringLiteral("lon")).toDouble());
            item.setCountry(attrsMap.value(QStringLiteral("country")).toString());
            item.setName(attrsMap.value(QStringLiteral("name")).toString());
            item.setHost(attrsMap.value(QStringLiteral("host")).toString());
            item.setSponsor(attrsMap.value(QStringLiteral("sponsor")).toString());
            item.setUrl(attrsMap.value(QStringLiteral("url")).toString());

            qint32 lastUrlIdx = item.url().lastIndexOf(QStringLiteral("/"));
            if(lastUrlIdx == -1)
                continue;

            item.setLatencyUrl( item.url().left(lastUrlIdx+1) + QStringLiteral("latency.txt") );
            item.setDistance( Private::measure(item.latitude(), item.longitude(), clat, clon) );

            p->items << item;
        }
        n = n.nextSibling();
    }

    p->fetched = true;
    Q_EMIT changed();
}

STServerList::~STServerList()
{
    delete p;
}
