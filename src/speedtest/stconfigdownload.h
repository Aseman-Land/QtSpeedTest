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

#ifndef STCONFIGDOWNLOAD_H
#define STCONFIGDOWNLOAD_H

#include <QString>
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STConfigDownload
{
public:
    STConfigDownload();
    STConfigDownload(class QDomNamedNodeMap *xml);
    virtual ~STConfigDownload();

    qint32 testLength() const;
    void setTestLength(const qint32 &testLength);

    qint64 initialTest() const;
    void setInitialTest(const qint64 &initialTest);

    qint64 intestSize() const;
    void setIntestSize(const qint64 &intestSize);

    qint32 threadsPerUrl() const;
    void setThreadsPerUrl(const qint32 &threadsPerUrl);

private:
    qint32 mTestLength;
    qint64 mInitialTest;
    qint64 mIntestSize;
    qint32 mThreadsPerUrl;
};

#endif // STCONFIGDOWNLOAD_H
