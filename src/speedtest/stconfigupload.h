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

#ifndef STCONFIGUPLOAD_H
#define STCONFIGUPLOAD_H

#include <QString>
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STConfigUpload
{
public:
    STConfigUpload();
    STConfigUpload(class QDomNamedNodeMap *xml);
    virtual ~STConfigUpload();

    qint32 testLength() const;
    void setTestLength(const qint32 &testLength);

    qint32 ratio() const;
    void setRatio(const qint32 &ratio);

    qint32 initialTest() const;
    void setInitialTest(const qint32 &initialTest);

    qint64 mintestSize() const;
    void setMintestSize(const qint64 &mintestSize);

    qint32 threads() const;
    void setThreads(const qint32 &threads);

    qint64 maxChunkSize() const;
    void setMaxChunkSize(const qint64 &maxChunkSize);

    qint32 maxChunkCount() const;
    void setMaxChunkCount(const qint32 &maxChunkCount);

    qint32 threadsPerUrl() const;
    void setThreadsPerUrl(const qint32 &threadsPerUrl);

private:
    qint32 mTestLength;
    qint32 mRatio;
    qint32 mInitialTest;
    qint64 mMintestSize;
    qint32 mThreads;
    qint64 mMaxChunkSize;
    qint32 mMaxChunkCount;
    qint32 mThreadsPerUrl;
};

#endif // STCONFIGUPLOAD_H
