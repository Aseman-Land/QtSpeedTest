load(qt_build_config)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = QtSpeedTest
QT = core network xml

MODULE_PRI = ../../modules/qt_speedtest.pri
MODULE = speedtest

load(qt_module)

DEFINES += LIBQSPEEDTEST_LIBRARY

SOURCES += \
    $$PWD/speedtest.cpp \
    $$PWD/stserversorter.cpp \
    $$PWD/stserveritem.cpp \
    $$PWD/stserverlist.cpp \
    $$PWD/stconfigclient.cpp \
    $$PWD/stconfigdownload.cpp \
    $$PWD/stconfigupload.cpp \
    $$PWD/stconfigdownloadsocket.cpp \
    $$PWD/stconfiguploadsocket.cpp \
    $$PWD/stconfiglatency.cpp \
    $$PWD/stconfigglobal.cpp \
    $$PWD/stdownloader.cpp \
    $$PWD/stclient.cpp \
    $$PWD/stuploader.cpp \
    $$PWD/stdummybuffer.cpp \
    stuploaderhttp.cpp

HEADERS += \
    $$PWD/speedtest.h \
    $$PWD/stserversorter.h \
    $$PWD/stserveritem.h \
    $$PWD/stserverlist.h \
    $$PWD/stconfigclient.h \
    $$PWD/stconfigdownload.h \
    $$PWD/stconfigupload.h \
    $$PWD/stconfigdownloadsocket.h \
    $$PWD/stconfiguploadsocket.h \
    $$PWD/stconfiglatency.h \
    $$PWD/stconfigglobal.h \
    $$PWD/stdownloader.h \
    $$PWD/stclient.h \
    $$PWD/stuploader.h \
    $$PWD/stdummybuffer.h \
    $$PWD/speedtest_p.h \
    $$PWD/libqspeedtest_global.h \
    stuploaderhttp.h
