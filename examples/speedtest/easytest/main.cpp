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

#include <speedtest.h>

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SpeedTest sp;

    sp.connect(&sp, &SpeedTest::errorStringChanged, &sp, [&sp](){
        qDebug() << "Err:" << sp.errorString();
    });
    sp.connect(&sp, &SpeedTest::statusStringChanged, &sp, [&sp](){
        qDebug() << "Stt:" << sp.statusString();
    });
    sp.connect(&sp, &SpeedTest::statusChanged, &sp, [&sp, &a](){
        if(sp.status() == SpeedTest::FinishedStatus)
            a.quit();
    });

    sp.start();
    return a.exec();
}
