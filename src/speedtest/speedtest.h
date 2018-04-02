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

#ifndef SPEEDTEST_H
#define SPEEDTEST_H

#include <QObject>
#include <QVariantMap>

#include "stclient.h"
#include "stserverlist.h"
#include "stserversorter.h"
#include "stdownloader.h"
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT SpeedTest : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_ENUMS(Error)

    class Private;

    Q_PROPERTY(Error error READ error NOTIFY errorChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
    Q_PROPERTY(QString statusString READ statusString NOTIFY statusStringChanged)
    Q_PROPERTY(QVariantMap bestServer READ bestServer NOTIFY bestServerChanged)

public:
    enum Status {
        UnknownStatus,
        RetrievingConfiguration,
        RetrievingServerList,
        FindingClosestServer,
        Downloading,
        Uploading,
        FinishedStatus
    };

    enum Error {
        NoError,
        GetConfigsError,
        GetServerListError,
        FindClosestServerError,
        DownloadError
    };

    SpeedTest(QObject *parent = Q_NULLPTR);
    virtual ~SpeedTest();

    void setConfigsUrl(const QString &configsUrl);
    QString configsUrl() const;

    void setServersUrl(const QString &serversUrl);
    QString serversUrl() const;

    void setUserAgent(const QString &userAgent);
    QString userAgent() const;

    void setCountry(const QString &country);
    QString country() const;

    STClient *client() const;
    STServerList *serverList() const;
    STServerSorter *sorter() const;

    STDownloader *downloader() const;

    Error error() const;
    QString errorString() const;

    Status status() const;
    QString statusString() const;
    void setStatusString(const QString &statusString);

    QVariantMap configs() const;
    QVariantMap bestServer() const;
    STServerSorterItem bestServerItem() const;

Q_SIGNALS:
    void errorChanged();
    void errorStringChanged();
    void statusChanged();
    void bestServerChanged();
    void statusStringChanged();

    void finished();

public Q_SLOTS:
    void start();
    void clearCache();

private:
    void clientChanged();
    void serversChanged();
    void sortsChanged();
    void downloadFinished();
    void uploadFinished();

    void clientError();
    void serversError();
    void sorterError();
    void downloaderError();
    void uploaderError();

    void findingBestServers();

    STServerSorterItem findBestServer();

    void setError(Error error);
    void setErrorString(const QString &error);
    void setStatus(Status status);

    void storeServerList();
    void loadServerList();

private:
    Private *p;
};

Q_DECLARE_METATYPE(SpeedTest::Status)
Q_DECLARE_METATYPE(SpeedTest::Error)

#endif // SPEEDTEST_H
