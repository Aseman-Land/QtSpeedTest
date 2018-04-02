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

#ifndef STCONFIGCLIENT_H
#define STCONFIGCLIENT_H

#include <QString>
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STConfigClient
{
public:
    STConfigClient();
    STConfigClient(class QDomNamedNodeMap *xml);
    virtual ~STConfigClient();

    QString ip() const;
    void setIp(const QString &ip);

    qreal latitude() const;
    void setLatitude(qreal latitude);

    qreal longitude() const;
    void setLongitude(qreal longitude);

    qreal rating() const;
    void setRating(qreal rating);

    QString isp() const;
    void setIsp(const QString &isp);

    qreal ispRating() const;
    void setIspRating(qreal ispRating);

    qreal ispDownloadAverage() const;
    void setIspDownloadAverage(qreal ispDownloadAverage);

    qreal ispUploadAverage() const;
    void setIspUploadAverage(qreal ispUploadAverage);

private:
    QString mIp;
    qreal mLatitude;
    qreal mLongitude;
    qreal mRating;
    QString mIsp;
    qreal mIspRating;
    qreal mIspDownloadAverage;
    qreal mIspUploadAverage;
};

#endif // STCONFIGCLIENT_H
