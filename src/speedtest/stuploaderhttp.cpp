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

#include "stdummybuffer.h"
#include "stuploaderhttp.h"

#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class STUploaderHttp::Private
{
public:
    QHash<QNetworkReply*, qint64> replies;

    QNetworkAccessManager *manager;
    STClient *client;

    QDateTime startTime;
    QDateTime readyTime;
    QDateTime finishTime;
    qint64 totalBytes;

    QString error;
    STUploaderHttp::Status status;
};

STUploaderHttp::STUploaderHttp(STClient *client, QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->totalBytes = 0;
    p->status = Idle;
    p->client = client;
    p->manager = new QNetworkAccessManager(this);
}

qint32 STUploaderHttp::delayTime() const
{
    if(p->startTime == p->readyTime)
        return -1;

    return p->startTime.msecsTo(p->readyTime);
}

qint32 STUploaderHttp::uploadTime() const
{
    if(p->readyTime == p->finishTime)
        return -1;

    return p->readyTime.msecsTo(p->finishTime);
}

qint32 STUploaderHttp::uploadBytes() const
{
    qint32 res = p->totalBytes;
    for(qint64 bytes: p->replies)
        res += bytes;
    return res;
}

QString STUploaderHttp::error() const
{
    return p->error;
}

void STUploaderHttp::setError(const QString &error)
{
    if(p->error == error)
        return;

    p->error = error;
    Q_EMIT errorChanged();
}

STUploaderHttp::Status STUploaderHttp::status() const
{
    return p->status;
}

void STUploaderHttp::setStatus(STUploaderHttp::Status status)
{
    if(p->status >= status)
        return;

    p->status = status;
    Q_EMIT statusChanged();
}

void STUploaderHttp::start(const STServerItem &server, qint32 timeout, qint32 threads)
{
    for(QNetworkReply *reply: p->replies.keys())
        reply->deleteLater();
    p->replies.clear();

    p->totalBytes = 0;
    p->startTime = QDateTime::currentDateTime();
    p->readyTime = p->startTime;
    p->finishTime = p->startTime;

    QNetworkRequest req;
    req.setHeader(QNetworkRequest::UserAgentHeader, p->client->userAgent());
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
    req.setUrl(server.url());

    for(qint32 i=0; i<threads; i++)
    {
        STDummyBuffer *buffer = new STDummyBuffer(1000000000);
        buffer->open(STDummyBuffer::ReadOnly);

        QNetworkReply *reply = p->manager->post(req, buffer);
        buffer->setParent(reply);

        QTimer *timer = new QTimer(reply);
        timer->setInterval(timeout);
        timer->setSingleShot(true);

        setStatus(Connecting);
        connect(reply, &QNetworkReply::finished, this, [this, reply](){
            reply->deleteLater();
        });
        connect(reply, &QNetworkReply::uploadProgress, this, [this, reply](qint64 bytesSent, qint64){
            if(p->readyTime != p->startTime)
                p->readyTime = QDateTime::currentDateTime();

            p->replies[reply] = bytesSent;
            p->finishTime = QDateTime::currentDateTime();
            setStatus(Uploading);
            Q_EMIT uploadTimeChanged();
            Q_EMIT uploadBytesChanged();
        });
        connect(reply, &QNetworkReply::destroyed, this, [this, reply](){
            p->totalBytes += p->replies.take(reply);
            if(p->replies.isEmpty())
            {
                setStatus(Finished);
                Q_EMIT finished();
            }
        });
        connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [this, reply](){
            setError(reply->errorString());
        });

        connect(timer, &QTimer::timeout, reply, &QNetworkReply::deleteLater);
        timer->start();

        p->replies.insert(reply, 0);
    }

    Q_EMIT delayTimeChanged();
    Q_EMIT uploadTimeChanged();
    Q_EMIT uploadBytesChanged();
}

STUploaderHttp::~STUploaderHttp()
{
    delete p;
}
