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

#define CACHE_SERVER_FILE QString(p->cachePath + QStringLiteral("/servers.json"))

#include "speedtest.h"
#include "stclient.h"
#include "stdownloader.h"
#include "stserverlist.h"
#include "stserversorter.h"
#include "stuploader.h"

#include <QDir>
#include <QUuid>
#include <QStandardPaths>
#include <QHash>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QJsonDocument>

class SpeedTest::Private
{
public:
    STClient *client;
    STServerList *serverList;
    STServerSorter *sorter;

    QString cachePath;

    SpeedTest::Status status;
    QString statusString;

    SpeedTest::Error error;
    QString errorString;

    QVariantMap configs;
    STServerSorterItem bestServer;

    STDownloader *downloader;
    STUploader *uploader;
};

SpeedTest::SpeedTest(QObject *parent) :
    QObject(parent)
{
    p = new Private;

    p->client = new STClient(this);
    p->serverList = new STServerList(p->client, this);
    p->sorter = new STServerSorter(p->serverList, this);

    p->downloader = new STDownloader(p->client, this);
    p->uploader = new STUploader(p->client, this);

    QStringList cachePaths = QStandardPaths::standardLocations(QStandardPaths::CacheLocation);
    cachePaths << QDir::homePath() + QStringLiteral("/.cache");

    p->cachePath = cachePaths.first() + QStringLiteral("/qtspeedtest/");

    QDir().mkpath(p->cachePath);

    connect(p->client, &STClient::configsChanged, this, &SpeedTest::clientChanged);
    connect(p->serverList, &STServerList::changed, this, &SpeedTest::serversChanged);
    connect(p->sorter, &STServerSorter::changed, this, &SpeedTest::sortsChanged);
    connect(p->downloader, &STDownloader::finished, this, &SpeedTest::downloadFinished);
    connect(p->uploader, &STUploader::finished, this, &SpeedTest::uploadFinished);

    connect(p->client, &STClient::errorChanged, this, &SpeedTest::clientError);
    connect(p->serverList, &STServerList::errorChanged, this, &SpeedTest::serversError);
    connect(p->sorter, &STServerSorter::errorChanged, this, &SpeedTest::sorterError);
    connect(p->downloader, &STDownloader::errorChanged, this, &SpeedTest::downloaderError);
    connect(p->uploader, &STUploader::errorChanged, this, &SpeedTest::uploaderError);

    p->status = UnknownStatus;
    p->error = NoError;
}

void SpeedTest::start()
{
    setStatus(RetrievingConfiguration);
    setStatusString( QStringLiteral("Retrieving configuration from server...") );
    p->client->fetch();
}

void SpeedTest::clearCache()
{
    QFile::remove(CACHE_SERVER_FILE);
}

void SpeedTest::clientChanged()
{
    QFileInfo info(CACHE_SERVER_FILE);
    if(info.exists())
    {
        if(info.created().daysTo(QDateTime::currentDateTime()) > 7)
            setStatusString( QStringLiteral("Updating servers list from server...") );
        else
        {
            setStatusString( QStringLiteral("Servers list is updated.") );
            loadServerList();
            return;
        }
    }
    else
        setStatusString( QStringLiteral("Retrieving servers list from server...") );

    setStatus(RetrievingServerList);
    p->serverList->fetch();
}

void SpeedTest::serversChanged()
{
    if(p->serverList->fetched())
        storeServerList();
    setStatus(FindingClosestServer);
    setStatusString( QStringLiteral("Check latencies...") );
    p->sorter->sortByLatency( p->client->latencyConfig().timeout()*1000 );
}

void SpeedTest::sortsChanged()
{
    STServerSorterItem item = findBestServer();
    setStatusString( QString(QStringLiteral("Selected server: %1 (%2) [%3km]: %4ms")).arg(item.sponsor()).arg(item.name())
                     .arg(item.distance()).arg(item.latency()));

    setStatus(Downloading);
    setStatusString(QStringLiteral("Downloading..."));
    p->downloader->start(item, p->client->downloadConfig().testLength()*1000,
                               p->client->downloadConfig().threadsPerUrl());
}

void SpeedTest::downloadFinished()
{
    STServerSorterItem item = bestServerItem();
    setStatusString( QString(QStringLiteral("Download Speed: %1kbps")).arg( 8*p->downloader->downloadBytes()/p->downloader->downloadTime() ));
    setStatus(Uploading);
    setStatusString(QStringLiteral("Uploading..."));
    p->uploader->start(item, p->client->uploadConfig().testLength()*1000,
                             p->client->uploadConfig().threadsPerUrl());
}

void SpeedTest::uploadFinished()
{
    setStatusString( QString(QStringLiteral("Upload Speed: %1kbps")).arg( 8*p->uploader->uploadBytes()/p->uploader->uploadTime() ));
    setStatus(FinishedStatus);
    setStatusString(QStringLiteral("Finished"));

}

void SpeedTest::clientError()
{
    setError(GetConfigsError);
    setErrorString(p->client->error());
    setStatus(FinishedStatus);
    setStatusString( QStringLiteral("Finished") );
}

void SpeedTest::serversError()
{
    setError(GetServerListError);
    setErrorString(p->serverList->error());
    setStatus(FinishedStatus);
    setStatusString( QStringLiteral("Finished") );
}

void SpeedTest::sorterError()
{
    setError(FindClosestServerError);
    setErrorString(p->sorter->error());
    setStatus(FinishedStatus);
    setStatusString( QStringLiteral("Finished") );
}

void SpeedTest::downloaderError()
{
    setError(DownloadError);
    setErrorString(p->downloader->error());
}

void SpeedTest::uploaderError()
{
    setError(UploadError);
    setErrorString(p->uploader->error());
}

STServerSorterItem SpeedTest::findBestServer()
{
    if(p->sorter->count())
        p->bestServer = p->sorter->item(0);
    else
        p->bestServer = STServerSorterItem();

    Q_EMIT bestServerChanged();
    return p->bestServer;
}

STClient *SpeedTest::client() const
{
    return p->client;
}

STServerList *SpeedTest::serverList() const
{
    return p->serverList;
}

STServerSorter *SpeedTest::sorter() const
{
    return p->sorter;
}

STDownloader *SpeedTest::downloader() const
{
    return p->downloader;
}

STUploader *SpeedTest::uploader() const
{
    return p->uploader;
}

SpeedTest::Error SpeedTest::error() const
{
    return p->error;
}

void SpeedTest::setError(SpeedTest::Error error)
{
    if(p->error == error)
        return;

    p->error = error;
    Q_EMIT errorChanged();
}

QString SpeedTest::errorString() const
{
    return p->errorString;
}

SpeedTest::Status SpeedTest::status() const
{
    return p->status;
}

QString SpeedTest::statusString() const
{
    return p->statusString;
}

void SpeedTest::setStatusString(const QString &statusString)
{
    if(p->statusString == statusString)
        return;

    p->statusString = statusString;
    Q_EMIT statusStringChanged();
}

void SpeedTest::setStatus(SpeedTest::Status status)
{
    if(p->status == status)
        return;

    p->status = status;
    Q_EMIT statusChanged();
    if(status == FinishedStatus)
        Q_EMIT finished();
}

void SpeedTest::storeServerList()
{
    QVariantList list;
    for(int i=0; i<p->serverList->count(); i++)
    {
        STServerItem item = p->serverList->item(i);
        QVariantMap map;
        map[QStringLiteral("latitude")] = item.latitude();
        map[QStringLiteral("longitude")] = item.longitude();
        map[QStringLiteral("country")] = item.country();
        map[QStringLiteral("distance")] = item.distance();
        map[QStringLiteral("host")] = item.host();
        map[QStringLiteral("latencyUrl")] = item.latencyUrl();
        map[QStringLiteral("name")] = item.name();
        map[QStringLiteral("sponsor")] = item.sponsor();
        map[QStringLiteral("url")] = item.url();

        list << map;
    }

    QFile file(CACHE_SERVER_FILE);
    if(!file.open(QFile::WriteOnly))
        return;

    file.write( QJsonDocument::fromVariant(list).toJson() );
    file.close();
}

void SpeedTest::loadServerList()
{
    QFile file(CACHE_SERVER_FILE);
    if(!file.open(QFile::ReadOnly))
        return;

    QVariantList list = QJsonDocument::fromJson(file.readAll()).toVariant().toList();
    file.close();

    QList<STServerItem> items;
    for(const QVariant &l: list)
    {
        QVariantMap map = l.toMap();
        STServerItem item;
        item.setLatitude( map.value(QStringLiteral("latitude")).toReal() );
        item.setLongitude( map.value(QStringLiteral("longitude")).toReal() );
        item.setCountry( map.value(QStringLiteral("country")).toString() );
        item.setDistance( map.value(QStringLiteral("distance")).toReal() );
        item.setHost( map.value(QStringLiteral("host")).toString() );
        item.setLatencyUrl( map.value(QStringLiteral("latencyUrl")).toString() );
        item.setName( map.value(QStringLiteral("name")).toString() );
        item.setSponsor( map.value(QStringLiteral("sponsor")).toString() );
        item.setUrl( map.value(QStringLiteral("url")).toString() );

        items << item;
    }

    p->serverList->setList(items);
}

QVariantMap SpeedTest::bestServer() const
{
    QVariantMap map;
    map[QStringLiteral("latitude")] = p->bestServer.latitude();
    map[QStringLiteral("longitude")] = p->bestServer.longitude();
    map[QStringLiteral("country")] = p->bestServer.country();
    map[QStringLiteral("latency")] = p->bestServer.latency();
    map[QStringLiteral("distance")] = p->bestServer.distance();
    map[QStringLiteral("host")] = p->bestServer.host();
    map[QStringLiteral("latencyUrl")] = p->bestServer.latencyUrl();
    map[QStringLiteral("name")] = p->bestServer.name();
    map[QStringLiteral("sponsor")] = p->bestServer.sponsor();
    map[QStringLiteral("url")] = p->bestServer.url();
    return map;
}

STServerSorterItem SpeedTest::bestServerItem() const
{
    return p->bestServer;
}

void SpeedTest::setErrorString(const QString &errorString)
{
    if(p->errorString == errorString)
        return;

    p->errorString = errorString;
    Q_EMIT errorStringChanged();
}

SpeedTest::~SpeedTest()
{
    delete p;
}
