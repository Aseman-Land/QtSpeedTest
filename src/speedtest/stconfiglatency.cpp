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

#include "stconfiglatency.h"
#include "stconfigglobal.h"

#include <QDomDocument>

STConfigLatency::STConfigLatency() :
    mTestLength(0),
    mWaitTime(0),
    mTimeout(0)
{

}

STConfigLatency::STConfigLatency(QDomNamedNodeMap *xml) :
    STConfigLatency()
{
    mTestLength = STConfigGlobal::readIntConfig(xml, QStringLiteral("testlength"));
    mWaitTime = STConfigGlobal::readIntConfig(xml, QStringLiteral("waittime"));
    mTimeout = STConfigGlobal::readIntConfig(xml, QStringLiteral("timeout"));
}

STConfigLatency::~STConfigLatency()
{

}

qint32 STConfigLatency::testLength() const
{
    return mTestLength;
}

void STConfigLatency::setTestLength(const qint32 &testLength)
{
    mTestLength = testLength;
}

qint32 STConfigLatency::waitTime() const
{
    return mWaitTime;
}

void STConfigLatency::setWaitTime(const qint32 &waitTime)
{
    mWaitTime = waitTime;
}

qint32 STConfigLatency::timeout() const
{
    return mTimeout;
}

void STConfigLatency::setTimeout(const qint32 &timeout)
{
    mTimeout = timeout;
}
