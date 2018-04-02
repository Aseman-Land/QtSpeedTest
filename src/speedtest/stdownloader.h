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

#ifndef STDOWNLOADER_H
#define STDOWNLOADER_H

#include <QObject>

#include "stclient.h"
#include "stserveritem.h"
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STDownloader : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)

    Q_PROPERTY(qint32 delayTime READ delayTime NOTIFY delayTimeChanged)
    Q_PROPERTY(qint32 downloadTime READ downloadTime NOTIFY downloadTimeChanged)
    Q_PROPERTY(qint32 downloadBytes READ downloadBytes NOTIFY downloadBytesChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)

    class Private;

public:
    enum Status {
        Idle,
        Connecting,
        Requesting,
        Downloading,
        Finished
    };

    STDownloader(STClient *client, QObject *parent = Q_NULLPTR);
    virtual ~STDownloader();

    qint32 delayTime() const;
    qint32 downloadTime() const;
    qint32 downloadBytes() const;

    QString error() const;
    Status status() const;

Q_SIGNALS:
    void finished();
    void delayTimeChanged();
    void downloadTimeChanged();
    void downloadBytesChanged();
    void errorChanged();
    void statusChanged();

public Q_SLOTS:
    void start(const STServerItem &server, qint32 timeout = 10000, qint32 threads = 1);

private:
    void setError(const QString &error);
    void setStatus(Status status);

private:
    Private *p;
};

Q_DECLARE_METATYPE(STDownloader::Status)

#endif // STDOWNLOADER_H
