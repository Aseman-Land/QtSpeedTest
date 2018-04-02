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

#ifndef  ASEMANDUMMYBUFFER_H
#define  ASEMANDUMMYBUFFER_H

#include <QIODevice>
#include "libqspeedtest_global.h"

class LIBQSPEEDTESTSHARED_EXPORT STDummyBuffer : public QIODevice
{
    Q_OBJECT
public:
    STDummyBuffer(qint64 size, QObject *parent = Q_NULLPTR);
    virtual ~STDummyBuffer();

    virtual bool open(OpenMode flags);
    virtual qint64 size() const;

protected:
    virtual qint64 readData(char *data, qint64 maxlen);
    virtual qint64 writeData(const char *data, qint64 len);

private:
    qint64 mSize;
};

#endif //  ASEMANDUMMYBUFFER_H
