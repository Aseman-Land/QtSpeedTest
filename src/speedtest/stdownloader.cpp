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

#include "stdownloader.h"

#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>
#include <QTimer>

class STDownloader::Private
{
public:
    QSet<QTcpSocket*> sockets;
    STClient *client;

    QDateTime startTime;
    QDateTime readyTime;
    QDateTime finishTime;
    qint64 totalBytes;

    QString error;
    STDownloader::Status status;
};

STDownloader::STDownloader(STClient *client, QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->totalBytes = 0;
    p->status = Idle;
    p->client = client;
}

qint32 STDownloader::delayTime() const
{
    if(p->startTime == p->readyTime)
        return -1;

    return p->startTime.msecsTo(p->readyTime);
}

qint32 STDownloader::downloadTime() const
{
    if(p->readyTime == p->finishTime)
        return -1;

    return p->readyTime.msecsTo(p->finishTime);
}

qint32 STDownloader::downloadBytes() const
{
    return p->totalBytes;
}

QString STDownloader::error() const
{
    return p->error;
}

void STDownloader::setError(const QString &error)
{
    if(p->error == error)
        return;

    p->error = error;
    Q_EMIT errorChanged();
}

STDownloader::Status STDownloader::status() const
{
    return p->status;
}

void STDownloader::setStatus(STDownloader::Status status)
{
    if(p->status >= status)
        return;

    p->status = status;
    Q_EMIT statusChanged();
}

void STDownloader::start(const STServerItem &server, qint32 timeout, qint32 threads)
{
    for(QTcpSocket *socket: p->sockets)
        socket->deleteLater();
    p->sockets.clear();

    QString hostStr = server.host();
    qint32 idx = hostStr.indexOf( QStringLiteral(":") );
    if(idx < 0)
    {
        setError( QStringLiteral("Invalid server") );
        return;
    }

    QString host = hostStr.left(idx);
    qint32 port = hostStr.mid(idx+1).toInt();

    p->totalBytes = 0;
    p->startTime = QDateTime::currentDateTime();
    p->readyTime = p->startTime;
    p->finishTime = p->startTime;

    for(qint32 i=0; i<threads; i++)
    {
        QTcpSocket *socket = new QTcpSocket(this);

        QTimer *timer = new QTimer(socket);
        timer->setInterval(timeout);
        timer->setSingleShot(true);

        setStatus(Connecting);
        connect(socket, &QTcpSocket::connected, this, [this, socket](){
            if(p->readyTime != p->startTime)
                p->readyTime = QDateTime::currentDateTime();

            socket->write("DOWNLOAD 1000000000\n");
            setStatus(Requesting);
            Q_EMIT delayTimeChanged();
        });
        connect(socket, &QTcpSocket::disconnected, this, [this, socket](){
            socket->deleteLater();
        });
        connect(socket, &QTcpSocket::readyRead, this, [this, socket](){
            p->totalBytes += socket->readAll().size();
            p->finishTime = QDateTime::currentDateTime();
            setStatus(Downloading);
            Q_EMIT downloadTimeChanged();
            Q_EMIT downloadBytesChanged();
        });
        connect(socket, &QTcpSocket::destroyed, this, [this, socket](){
            p->sockets.remove(socket);
            if(p->sockets.isEmpty())
            {
                setStatus(Finished);
                Q_EMIT finished();
            }
        });
        connect(socket, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, [this, socket](){
            setError(socket->errorString());
        });
        connect(timer, &QTimer::timeout, socket, &QTcpSocket::deleteLater);

        p->sockets.insert(socket);

        timer->start();
        socket->connectToHost(host, port);
    }

    Q_EMIT delayTimeChanged();
    Q_EMIT downloadTimeChanged();
    Q_EMIT downloadBytesChanged();
}

STDownloader::~STDownloader()
{
    delete p;
}
