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

#ifndef STSERVERLIST_H
#define STSERVERLIST_H

#include "stclient.h"
#include "stserveritem.h"
#include "libqspeedtest_global.h"

#include <QObject>

class LIBQSPEEDTESTSHARED_EXPORT STServerList : public QObject
{
    Q_OBJECT
    class Private;
    Q_PROPERTY(QString serversUrl READ serversUrl WRITE setServersUrl NOTIFY serversUrlChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(qint32 count READ count NOTIFY changed)

public:
    STServerList(STClient *client, QObject *parent = Q_NULLPTR);
    virtual ~STServerList();

    qint32 count() const;
    STServerItem item(qint32 idx) const;

    void setServersUrl(const QString &serversUrl);
    QString serversUrl() const;

    QString error() const;
    STClient *client() const;

    void setList(const QList<STServerItem> &items);
    bool fetched() const;

Q_SIGNALS:
    void changed();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void serversUrlChanged();
    void errorChanged();

public Q_SLOTS:
    void fetch();

private:
    void analizeData();
    void setError(const QString &error);

private:
    Private *p;
};

#endif // STSERVERLIST_H
