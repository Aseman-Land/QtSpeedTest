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

#ifndef STCONFIGDOWNLOADSOCKET_H
#define STCONFIGDOWNLOADSOCKET_H

#include <QString>
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STConfigDownloadSocket
{
public:
    STConfigDownloadSocket();
    STConfigDownloadSocket(class QDomNamedNodeMap *xml);
    virtual ~STConfigDownloadSocket();

    qint32 testLength() const;
    void setTestLength(const qint32 &testLength);

    qint32 initialThreads() const;
    void setInitialThreads(const qint32 &initialThreads);

    qint32 minThreads() const;
    void setMinThreads(const qint32 &minThreads);

    qint32 maxThreads() const;
    void setMaxThreads(const qint32 &maxThreads);

    qint32 threadRatio() const;
    void setThreadRatio(const qint32 &threadRatio);

    qint32 maxSampleSize() const;
    void setMaxSampleSize(const qint32 &maxSampleSize);

    qint32 minSampleSize() const;
    void setMinSampleSize(const qint32 &minSampleSize);

    qint32 startSampleSize() const;
    void setStartSampleSize(const qint32 &startSampleSize);

    qint32 startBufferSize() const;
    void setStartBufferSize(const qint32 &startBufferSize);

    qint32 bufferLength() const;
    void setBufferLength(const qint32 &bufferLength);

    qint32 packetLength() const;
    void setPacketLength(const qint32 &packetLength);

    qint32 readBuffer() const;
    void setReadBuffer(const qint32 &readBuffer);

private:
    qint32 mTestLength;
    qint32 mInitialThreads;
    qint32 mMinThreads;
    qint32 mMaxThreads;
    qint32 mThreadRatio;
    qint32 mMaxSampleSize;
    qint32 mMinSampleSize;
    qint32 mStartSampleSize;
    qint32 mStartBufferSize;
    qint32 mBufferLength;
    qint32 mPacketLength;
    qint32 mReadBuffer;
};

#endif // STCONFIGDOWNLOADSOCKET_H
