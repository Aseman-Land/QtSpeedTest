QT.speedtest.VERSION = 5.0.0
QT.speedtest.MAJOR_VERSION = 5
QT.speedtest.MINOR_VERSION = 0
QT.speedtest.PATCH_VERSION = 0

QT.speedtest.name = QtSpeedTest
QT.speedtest.bins = $$QT_MODULE_BIN_BASE
QT.speedtest.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtSpeedTest
QT.speedtest.private_includes = $$QT_MODULE_INCLUDE_BASE/QtSpeedTest/$$QT.speedtest.VERSION
QT.speedtest.sources = $$QT_MODULE_BASE/src/qspeedtest
QT.speedtest.libs = $$QT_MODULE_LIB_BASE
QT.speedtest.plugins = $$QT_MODULE_PLUGIN_BASE
QT.speedtest.imports = $$QT_MODULE_IMPORT_BASE
QT.speedtest.depends = core network
