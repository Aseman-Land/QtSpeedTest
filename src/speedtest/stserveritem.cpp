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

#include "stserveritem.h"

STServerItem::STServerItem() :
    mLatitude(0),
    mLongitude(0),
    mDistance(0)
{
}

STServerItem::~STServerItem()
{
}

qreal STServerItem::latitude() const
{
    return mLatitude;
}

void STServerItem::setLatitude(qreal clat)
{
    mLatitude = clat;
}

qreal STServerItem::longitude() const
{
    return mLongitude;
}

void STServerItem::setLongitude(qreal clon)
{
    mLongitude = clon;
}

qreal STServerItem::distance() const
{
    return mDistance;
}

void STServerItem::setDistance(qreal distance)
{
    mDistance = distance;
}

QString STServerItem::country() const
{
    return mCountry;
}

void STServerItem::setCountry(const QString &country)
{
    mCountry = country;
}

QString STServerItem::name() const
{
    return mName;
}

void STServerItem::setName(const QString &name)
{
    mName = name;
}

QString STServerItem::host() const
{
    return mHost;
}

void STServerItem::setHost(const QString &host)
{
    mHost = host;
}

QString STServerItem::sponsor() const
{
    return mSponsor;
}

void STServerItem::setSponsor(const QString &sponsor)
{
    mSponsor = sponsor;
}

QString STServerItem::url() const
{
    return mUrl;
}

void STServerItem::setUrl(const QString &url)
{
    mUrl = url;
}

QString STServerItem::latencyUrl() const
{
    return mLatencyUrl;
}

void STServerItem::setLatencyUrl(const QString &latencyUrl)
{
    mLatencyUrl = latencyUrl;
}
