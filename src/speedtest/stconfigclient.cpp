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

#include "stconfigclient.h"

#include <QDomDocument>

STConfigClient::STConfigClient() :
    mLatitude(0),
    mLongitude(0),
    mRating(0),
    mIspRating(0),
    mIspDownloadAverage(0),
    mIspUploadAverage(0)
{
}

STConfigClient::STConfigClient(QDomNamedNodeMap *xml) :
    STConfigClient()
{
    mIp = xml->namedItem(QStringLiteral("ip")).nodeValue();
    mLatitude = xml->namedItem(QStringLiteral("lat")).nodeValue().toDouble();
    mLongitude = xml->namedItem(QStringLiteral("lon")).nodeValue().toDouble();
    mRating = xml->namedItem(QStringLiteral("rating")).nodeValue().toDouble();
    mIsp = xml->namedItem(QStringLiteral("isp")).nodeValue();
    mIspRating = xml->namedItem(QStringLiteral("isprating")).nodeValue().toDouble();
    mIspDownloadAverage = xml->namedItem(QStringLiteral("ispdlavg")).nodeValue().toDouble();
    mIspUploadAverage = xml->namedItem(QStringLiteral("ispulavg")).nodeValue().toDouble();
}

STConfigClient::~STConfigClient()
{
}

QString STConfigClient::ip() const
{
    return mIp;
}

void STConfigClient::setIp(const QString &ip)
{
    mIp = ip;
}

qreal STConfigClient::latitude() const
{
    return mLatitude;
}

void STConfigClient::setLatitude(qreal latitude)
{
    mLatitude = latitude;
}

qreal STConfigClient::longitude() const
{
    return mLongitude;
}

void STConfigClient::setLongitude(qreal longitude)
{
    mLongitude = longitude;
}

qreal STConfigClient::rating() const
{
    return mRating;
}

void STConfigClient::setRating(qreal rating)
{
    mRating = rating;
}

QString STConfigClient::isp() const
{
    return mIsp;
}

void STConfigClient::setIsp(const QString &isp)
{
    mIsp = isp;
}

qreal STConfigClient::ispRating() const
{
    return mIspRating;
}

void STConfigClient::setIspRating(qreal ispRating)
{
    mIspRating = ispRating;
}

qreal STConfigClient::ispDownloadAverage() const
{
    return mIspDownloadAverage;
}

void STConfigClient::setIspDownloadAverage(qreal ispDownloadAverage)
{
    mIspDownloadAverage = ispDownloadAverage;
}

qreal STConfigClient::ispUploadAverage() const
{
    return mIspUploadAverage;
}

void STConfigClient::setIspUploadAverage(qreal ispUploadAverage)
{
    mIspUploadAverage = ispUploadAverage;
}
