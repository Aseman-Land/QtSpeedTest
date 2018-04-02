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

#include "stconfigdownloadsocket.h"
#include "stconfigglobal.h"

#include <QDomDocument>

STConfigDownloadSocket::STConfigDownloadSocket() :
    mTestLength(0),
    mInitialThreads(0),
    mMinThreads(0),
    mMaxThreads(0),
    mThreadRatio(0),
    mMaxSampleSize(0),
    mMinSampleSize(0),
    mStartSampleSize(0),
    mStartBufferSize(0),
    mBufferLength(0),
    mPacketLength(0),
    mReadBuffer(0)
{
}

STConfigDownloadSocket::STConfigDownloadSocket(QDomNamedNodeMap *xml) :
    STConfigDownloadSocket()
{
    mTestLength = STConfigGlobal::readIntConfig(xml, QStringLiteral("testlength"));
    mInitialThreads = STConfigGlobal::readIntConfig(xml, QStringLiteral("initialthreads"));
    mMinThreads = STConfigGlobal::readIntConfig(xml, QStringLiteral("minthreads"));
    mMaxThreads = STConfigGlobal::readIntConfig(xml, QStringLiteral("maxthreads"));
    mThreadRatio = STConfigGlobal::readIntConfig(xml, QStringLiteral("threadratio"));
    mMaxSampleSize = STConfigGlobal::readIntConfig(xml, QStringLiteral("maxsamplesize"));
    mMinSampleSize = STConfigGlobal::readIntConfig(xml, QStringLiteral("minsamplesize"));
    mStartSampleSize = STConfigGlobal::readIntConfig(xml, QStringLiteral("startsamplesize"));
    mStartBufferSize = STConfigGlobal::readIntConfig(xml, QStringLiteral("startbuffersize"));
    mBufferLength = STConfigGlobal::readIntConfig(xml, QStringLiteral("bufferlength"));
    mPacketLength = STConfigGlobal::readIntConfig(xml, QStringLiteral("packetlength"));
    mReadBuffer = STConfigGlobal::readIntConfig(xml, QStringLiteral("readbuffer"));
}

STConfigDownloadSocket::~STConfigDownloadSocket()
{

}

qint32 STConfigDownloadSocket::testLength() const
{
    return mTestLength;
}

void STConfigDownloadSocket::setTestLength(const qint32 &testLength)
{
    mTestLength = testLength;
}

qint32 STConfigDownloadSocket::initialThreads() const
{
    return mInitialThreads;
}

void STConfigDownloadSocket::setInitialThreads(const qint32 &initialThreads)
{
    mInitialThreads = initialThreads;
}

qint32 STConfigDownloadSocket::minThreads() const
{
    return mMinThreads;
}

void STConfigDownloadSocket::setMinThreads(const qint32 &minThreads)
{
    mMinThreads = minThreads;
}

qint32 STConfigDownloadSocket::maxThreads() const
{
    return mMaxThreads;
}

void STConfigDownloadSocket::setMaxThreads(const qint32 &maxThreads)
{
    mMaxThreads = maxThreads;
}

qint32 STConfigDownloadSocket::threadRatio() const
{
    return mThreadRatio;
}

void STConfigDownloadSocket::setThreadRatio(const qint32 &threadRatio)
{
    mThreadRatio = threadRatio;
}

qint32 STConfigDownloadSocket::maxSampleSize() const
{
    return mMaxSampleSize;
}

void STConfigDownloadSocket::setMaxSampleSize(const qint32 &maxSampleSize)
{
    mMaxSampleSize = maxSampleSize;
}

qint32 STConfigDownloadSocket::minSampleSize() const
{
    return mMinSampleSize;
}

void STConfigDownloadSocket::setMinSampleSize(const qint32 &minSampleSize)
{
    mMinSampleSize = minSampleSize;
}

qint32 STConfigDownloadSocket::startSampleSize() const
{
    return mStartSampleSize;
}

void STConfigDownloadSocket::setStartSampleSize(const qint32 &startSampleSize)
{
    mStartSampleSize = startSampleSize;
}

qint32 STConfigDownloadSocket::startBufferSize() const
{
    return mStartBufferSize;
}

void STConfigDownloadSocket::setStartBufferSize(const qint32 &startBufferSize)
{
    mStartBufferSize = startBufferSize;
}

qint32 STConfigDownloadSocket::bufferLength() const
{
    return mBufferLength;
}

void STConfigDownloadSocket::setBufferLength(const qint32 &bufferLength)
{
    mBufferLength = bufferLength;
}

qint32 STConfigDownloadSocket::packetLength() const
{
    return mPacketLength;
}

void STConfigDownloadSocket::setPacketLength(const qint32 &packetLength)
{
    mPacketLength = packetLength;
}

qint32 STConfigDownloadSocket::readBuffer() const
{
    return mReadBuffer;
}

void STConfigDownloadSocket::setReadBuffer(const qint32 &readBuffer)
{
    mReadBuffer = readBuffer;
}
