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

#include "stdummybuffer.h"

#include <QTime>

STDummyBuffer::STDummyBuffer(qint64 size, QObject *parent) :
    QIODevice(parent),
    mSize(size)
{
    qsrand(QTime::currentTime().msec());
}

bool STDummyBuffer::open(QIODevice::OpenMode flags)
{
    QIODevice::open(flags);
    return (flags == QIODevice::ReadOnly);
}

qint64 STDummyBuffer::size() const
{
    return mSize;
}

qint64 STDummyBuffer::readData(char *data, qint64 maxlen)
{
    if(atEnd())
        return -1;

    QByteArray src;
    for(int i=pos(); i<mSize && src.length()<maxlen; i++)
        src += (char)(qrand()%256);

    memcpy(data, src.constData(), src.size());
    return src.size();
}

qint64 STDummyBuffer::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data)
    Q_UNUSED(len)
    return -1;
}

STDummyBuffer::~STDummyBuffer()
{

}
