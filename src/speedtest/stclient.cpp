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

#include "stclient.h"

#include <QDomDocument>
#include <QNetworkReply>

class STClient::Private
{
public:
    QString configsUrl;
    QString userAgent;
    QNetworkAccessManager *manager;
    QHash<QNetworkReply*, QByteArray> buffers;

    STConfigClient clientConfig;
    STConfigDownload downloadConfig;
    STConfigDownloadSocket downloadSocketConfig;
    STConfigLatency latencyConfig;
    STConfigUpload uploadConfig;
    STConfigUploadSocket uploadSocketConfig;
    STConfigLatency socketLatencyConfig;

    QVariantMap configs;
    QString error;
};

STClient::STClient(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->configsUrl = QStringLiteral("http://www.speedtest.net/speedtest-config.php");
    p->userAgent = QStringLiteral("QtSpeedTest/1.0.0");

    p->manager = new QNetworkAccessManager(this);
}

void STClient::setConfigsUrl(const QString &configsUrl)
{
    if(p->configsUrl == configsUrl)
        return;

    p->configsUrl = configsUrl;
    Q_EMIT configsUrlChanged();
}

QString STClient::configsUrl() const
{
    return p->configsUrl;
}

void STClient::setUserAgent(const QString &userAgent)
{
    if(p->userAgent == userAgent)
        return;

    p->userAgent = userAgent;
    Q_EMIT userAgentChanged();
}

QString STClient::userAgent() const
{
    return p->userAgent;
}

STConfigClient STClient::clientConfig() const
{
    return p->clientConfig;
}

STConfigDownload STClient::downloadConfig() const
{
    return p->downloadConfig;
}

STConfigDownloadSocket STClient::downloadSocketConfig() const
{
    return p->downloadSocketConfig;
}

STConfigLatency STClient::latencyConfig() const
{
    return p->latencyConfig;
}

STConfigUpload STClient::uploadConfig() const
{
    return p->uploadConfig;
}

STConfigUploadSocket STClient::uploadSocketConfig() const
{
    return p->uploadSocketConfig;
}

STConfigLatency STClient::socketLatencyConfig() const
{
    return p->socketLatencyConfig;
}

QString STClient::error() const
{
    return p->error;
}

QVariantMap STClient::configs() const
{
    return p->configs;
}

void STClient::fetch()
{
    QNetworkRequest req;
    req.setHeader(QNetworkRequest::UserAgentHeader, p->userAgent);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    req.setUrl( QUrl(p->configsUrl) );

    QNetworkReply *reply = p->manager->get(req);

    connect(reply, &QNetworkReply::readyRead, this, [this, reply](){
        p->buffers[reply] += reply->readAll();
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        reply->deleteLater();
    });
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [this, reply](QNetworkReply::NetworkError){
        setError(QStringLiteral("Config file error: ") + reply->errorString());
    });
    connect(reply, &QNetworkReply::destroyed, this, [this, reply](){
        QByteArray data = p->buffers.take(reply);
        if(data.isEmpty())
        {
            setError(QStringLiteral("Empty config file"));
            return;
        }

        QDomDocument doc;
        QString errorMsg;
        if (!doc.setContent(data, &errorMsg))
        {
            setError(QStringLiteral("Config file error: ") + errorMsg);
            return;
        }

        QDomElement docElem = doc.documentElement();
        QDomNode n = docElem.firstChild();

        QVariantMap configs;

        while(!n.isNull())
        {
            QDomElement e = n.toElement();
            if(!e.isNull())
            {
                QDomNamedNodeMap attrs = e.attributes();
                if(e.tagName() == QStringLiteral("client"))
                    p->clientConfig = STConfigClient(&attrs);
                else
                if(e.tagName() == QStringLiteral("download"))
                    p->downloadConfig = STConfigDownload(&attrs);
                else
                if(e.tagName() == QStringLiteral("upload"))
                    p->uploadConfig = STConfigUpload(&attrs);
                else
                if(e.tagName() == QStringLiteral("socket-download"))
                    p->downloadSocketConfig = STConfigDownloadSocket(&attrs);
                else
                if(e.tagName() == QStringLiteral("socket-upload"))
                    p->uploadSocketConfig = STConfigUploadSocket(&attrs);
                else
                if(e.tagName() == QStringLiteral("latency"))
                    p->latencyConfig = STConfigLatency(&attrs);
                else
                if(e.tagName() == QStringLiteral("socket-latency"))
                    p->socketLatencyConfig = STConfigLatency(&attrs);

                QVariantMap attrsMap;
                for(int i=0; i<attrs.length(); i++)
                {
                    QDomNode node = attrs.item(i);
                    attrsMap[ node.nodeName() ] = node.nodeValue();
                }

                if(attrsMap.isEmpty())
                    configs[e.tagName()] = e.text();
                else
                    configs[e.tagName()] = attrsMap;
            }
            n = n.nextSibling();
        }

        setConfigs(configs);
    });
}

void STClient::setError(const QString &error)
{
    if(p->error == error)
        return;

    p->error = error;
    Q_EMIT errorChanged();
}

void STClient::setConfigs(const QVariantMap &configs)
{
    if(p->configs == configs)
        return;

    p->configs = configs;
    Q_EMIT configsChanged();
}

STClient::~STClient()
{
    delete p;
}
