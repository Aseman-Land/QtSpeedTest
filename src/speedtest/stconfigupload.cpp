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

#include "stconfigglobal.h"
#include "stconfigupload.h"

#include <QDomDocument>

STConfigUpload::STConfigUpload() :
    mTestLength(0),
    mRatio(0),
    mInitialTest(0),
    mMintestSize(0),
    mThreads(0),
    mMaxChunkSize(0),
    mMaxChunkCount(0),
    mThreadsPerUrl(0)
{

}

STConfigUpload::STConfigUpload(QDomNamedNodeMap *xml) :
    STConfigUpload()
{
    mTestLength = STConfigGlobal::readIntConfig(xml, QStringLiteral("testlength"));
    mRatio = STConfigGlobal::readIntConfig(xml, QStringLiteral("ratio"));
    mInitialTest = STConfigGlobal::readIntConfig(xml, QStringLiteral("initialtest"));
    mMintestSize = STConfigGlobal::readIntConfig(xml, QStringLiteral("mintestsize"));
    mThreads = STConfigGlobal::readIntConfig(xml, QStringLiteral("threads"));
    mMaxChunkSize = STConfigGlobal::readIntConfig(xml, QStringLiteral("maxchunksize"));
    mMaxChunkCount = STConfigGlobal::readIntConfig(xml, QStringLiteral("maxchunkcount"));
    mThreadsPerUrl = STConfigGlobal::readIntConfig(xml, QStringLiteral("threadsperurl"));
}

STConfigUpload::~STConfigUpload()
{

}

qint32 STConfigUpload::testLength() const
{
    return mTestLength;
}

void STConfigUpload::setTestLength(const qint32 &testLength)
{
    mTestLength = testLength;
}

qint32 STConfigUpload::ratio() const
{
    return mRatio;
}

void STConfigUpload::setRatio(const qint32 &ratio)
{
    mRatio = ratio;
}

qint32 STConfigUpload::initialTest() const
{
    return mInitialTest;
}

void STConfigUpload::setInitialTest(const qint32 &initialTest)
{
    mInitialTest = initialTest;
}

qint64 STConfigUpload::mintestSize() const
{
    return mMintestSize;
}

void STConfigUpload::setMintestSize(const qint64 &mintestSize)
{
    mMintestSize = mintestSize;
}

qint32 STConfigUpload::threads() const
{
    return mThreads;
}

void STConfigUpload::setThreads(const qint32 &threads)
{
    mThreads = threads;
}

qint64 STConfigUpload::maxChunkSize() const
{
    return mMaxChunkSize;
}

void STConfigUpload::setMaxChunkSize(const qint64 &maxChunkSize)
{
    mMaxChunkSize = maxChunkSize;
}

qint32 STConfigUpload::maxChunkCount() const
{
    return mMaxChunkCount;
}

void STConfigUpload::setMaxChunkCount(const qint32 &maxChunkCount)
{
    mMaxChunkCount = maxChunkCount;
}

qint32 STConfigUpload::threadsPerUrl() const
{
    return mThreadsPerUrl;
}

void STConfigUpload::setThreadsPerUrl(const qint32 &threadsPerUrl)
{
    mThreadsPerUrl = threadsPerUrl;
}
