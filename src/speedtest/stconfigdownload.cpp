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

#include "stconfigdownload.h"
#include "stconfigglobal.h"

#include<QDomDocument>

STConfigDownload::STConfigDownload() :
    mTestLength(0),
    mInitialTest(0),
    mIntestSize(0),
    mThreadsPerUrl(0)
{

}

STConfigDownload::STConfigDownload(QDomNamedNodeMap *xml) :
    STConfigDownload()
{
    mTestLength = STConfigGlobal::readIntConfig(xml, QStringLiteral("testlength"));
    mInitialTest = STConfigGlobal::readIntConfig(xml, QStringLiteral("initialtest"));
    mIntestSize = STConfigGlobal::readIntConfig(xml, QStringLiteral("mintestsize"));
    mThreadsPerUrl = STConfigGlobal::readIntConfig(xml, QStringLiteral("threadsperurl"));
}

STConfigDownload::~STConfigDownload()
{

}

qint32 STConfigDownload::testLength() const
{
    return mTestLength;
}

void STConfigDownload::setTestLength(const qint32 &testLength)
{
    mTestLength = testLength;
}

qint64 STConfigDownload::initialTest() const
{
    return mInitialTest;
}

void STConfigDownload::setInitialTest(const qint64 &initialTest)
{
    mInitialTest = initialTest;
}

qint64 STConfigDownload::intestSize() const
{
    return mIntestSize;
}

void STConfigDownload::setIntestSize(const qint64 &intestSize)
{
    mIntestSize = intestSize;
}

qint32 STConfigDownload::threadsPerUrl() const
{
    return mThreadsPerUrl;
}

void STConfigDownload::setThreadsPerUrl(const qint32 &threadsPerUrl)
{
    mThreadsPerUrl = threadsPerUrl;
}
