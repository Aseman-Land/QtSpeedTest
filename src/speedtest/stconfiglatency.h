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

#ifndef STCONFIGLATENCY_H
#define STCONFIGLATENCY_H

#include <QString>
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STConfigLatency
{
public:
    STConfigLatency();
    STConfigLatency(class QDomNamedNodeMap *xml);
    virtual ~STConfigLatency();

    qint32 testLength() const;
    void setTestLength(const qint32 &testLength);

    qint32 waitTime() const;
    void setWaitTime(const qint32 &waitTime);

    qint32 timeout() const;
    void setTimeout(const qint32 &timeout);

private:
    qint32 mTestLength;
    qint32 mWaitTime;
    qint32 mTimeout;
};

#endif // STCONFIGLATENCY_H
