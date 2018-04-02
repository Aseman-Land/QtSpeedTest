TARGET = easytest
QT += speedtest core
SOURCES += main.cpp

target = $$TARGET
target.path = $$[QT_INSTALL_EXAMPLES]/speedtest/easytest

INSTALLS += target
