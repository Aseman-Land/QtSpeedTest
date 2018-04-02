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

#ifndef STSERVERITEM_H
#define STSERVERITEM_H

#include <QString>
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STServerItem
{
public:
    STServerItem();
    virtual ~STServerItem();

    qreal latitude() const;
    void setLatitude(qreal latitude);

    qreal longitude() const;
    void setLongitude(qreal longitude);

    qreal distance() const;
    void setDistance(qreal distance);

    QString country() const;
    void setCountry(const QString &country);

    QString name() const;
    void setName(const QString &name);

    QString host() const;
    void setHost(const QString &host);

    QString sponsor() const;
    void setSponsor(const QString &sponsor);

    QString url() const;
    void setUrl(const QString &url);

    QString latencyUrl() const;
    void setLatencyUrl(const QString &latencyUrl);

    bool operator ==(const STServerItem &b) {
        return mHost== b.mHost &&
               mUrl == b.mUrl;
    }

private:
    qreal mLatitude;
    qreal mLongitude;
    qreal mDistance;
    QString mCountry;
    QString mName;
    QString mHost;
    QString mSponsor;
    QString mUrl;
    QString mLatencyUrl;
};

#endif // STSERVERITEM_H
