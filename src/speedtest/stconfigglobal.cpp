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

#include <QDomDocument>

STConfigGlobal::STConfigGlobal()
{

}

qint64 STConfigGlobal::readIntConfig(QDomNamedNodeMap *xml, const QString &attr)
{
    return xml->namedItem(attr).nodeValue().replace(QStringLiteral("K"), QStringLiteral("000"), Qt::CaseInsensitive)
                                           .replace(QStringLiteral("M"), QStringLiteral("000000"), Qt::CaseInsensitive)
                                           .replace(QStringLiteral("G"), QStringLiteral("000000000"), Qt::CaseInsensitive).toLongLong();
}

STConfigGlobal::~STConfigGlobal()
{

}
