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

#ifndef STSERVERSORTER_H
#define STSERVERSORTER_H

#include "stserverlist.h"
#include "libqspeedtest_global.h"

#include <QObject>

class LIBQSPEEDTESTSHARED_EXPORT STServerSorterItem: public STServerItem
{
public:
    STServerSorterItem(const STServerItem &another): STServerItem(another), mLatency(-1) {}
    STServerSorterItem(): STServerItem(), mLatency(-1) {}
    virtual ~STServerSorterItem() {}

    qint32 latency() const { return mLatency; }
    void setLatency(const qint32 &latency) { mLatency = latency; }

private:
    qint32 mLatency;
};

class LIBQSPEEDTESTSHARED_EXPORT STServerSorter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 limit READ limit WRITE setLimit NOTIFY limitChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

    class Private;

public:
    STServerSorter(STServerList *list, QObject *parent = Q_NULLPTR);
    virtual ~STServerSorter();

    void setLimit(qint32 limit);
    qint32 limit() const;

    qint32 count();
    STServerSorterItem item(qint32 idx);

    QString error() const;

public Q_SLOTS:
    void sortByLatency(qint32 timeout = 2000);
    void sortByDistance();

Q_SIGNALS:
    void limitChanged();
    void changed();
    void errorChanged();
    void latencyProgress(qint32 current, qint32 total);

private:
    void startCheckingLatencies(QList<STServerSorterItem> servers, qint32 total, qint32 timeout);
    void setError(const QString &error);

private:
    Private *p;
};

#endif // STSERVERSORTER_H
