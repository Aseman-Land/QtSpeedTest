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

#ifndef STCLIENT_H
#define STCLIENT_H

#include <QObject>
#include <QVariantMap>

#include "stconfigclient.h"
#include "stconfigdownload.h"
#include "stconfigdownloadsocket.h"
#include "stconfiglatency.h"
#include "stconfigupload.h"
#include "stconfiguploadsocket.h"
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString configsUrl READ configsUrl WRITE setConfigsUrl NOTIFY configsUrlChanged)
    Q_PROPERTY(QString userAgent READ userAgent WRITE setUserAgent NOTIFY userAgentChanged)
    Q_PROPERTY(QVariantMap configs READ configs NOTIFY configsChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

    class Private;

public:
    STClient(QObject *parent = Q_NULLPTR);
    virtual ~STClient();

    void setConfigsUrl(const QString &configsUrl);
    QString configsUrl() const;

    void setUserAgent(const QString &userAgent);
    QString userAgent() const;

    STConfigClient clientConfig() const;
    STConfigDownload downloadConfig() const;
    STConfigDownloadSocket downloadSocketConfig() const;
    STConfigLatency latencyConfig() const;
    STConfigUpload uploadConfig() const;
    STConfigUploadSocket uploadSocketConfig() const;
    STConfigLatency socketLatencyConfig() const;

    QString error() const;
    QVariantMap configs() const;

public Q_SLOTS:
    void fetch();

Q_SIGNALS:
    void configsUrlChanged();
    void userAgentChanged();
    void errorChanged();
    void configsChanged();

private:
    void setError(const QString &error);
    void setConfigs(const QVariantMap &configs);

private:
    Private *p;
};

#endif // STCLIENT_H
