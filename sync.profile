%modules = (
    "QtSpeedTest" => "$basedir/src/speedtest",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%classnames = (
);
%mastercontent = (
    "core" => "#include <QtCore/QtCore>",
    "network" => "#include <QtNetwork/QtNetwork>",
    "xml" => "#include <QtXml/QtXml>",
);
%modulepris = (
    "QtSpeedTest" => "$basedir/modules/qt_speedtest.pri",
);

%dependencies = (
        "qtbase" => ""
);
