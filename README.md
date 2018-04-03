# QtSpeedTest
Qt module and library Internet bandwidth testing using speedtest.net. It's written in C++/Qt and released under the LGPLv3 license.

Inspired by **[speedtest-lite](https://github.com/neutronth/speedtest-lite)** written by Neutron Soutmun (neutronth)

## Build

It's easy to build it. install Qt and dependencies:

```bash
sudo apt-get install g++ git qt5-default qtbase5-dev
```

And then build it:

```bash
git clone https://github.com/Aseman-Land/QtSpeedTest.git
cd QtSpeedTest
mkdir build && cd build
qmake .. PREFIX=/usr
make
sudo make install
```

## How to use it

It's easy too. Just add below line to the `.pro` file on your project

```perl
QT += speedtest
```

And include it in the source files:

```c++
#include <QtSpeedTest>

...
    
SpeedTest *sp = new SpeedTest();
connect(sp, &SpeedTest::errorStringChanged, this, [sp](){
    qDebug() << "Err:" << sp->errorString();
});
connect(sp, &SpeedTest::statusStringChanged, this, [sp](){
    qDebug() << "Stt:" << sp->statusString();
});
sp->start();
```

`SpeedTest` class is a high level class. But you can also using low-level classes like below classes:

1. `STClient`: To create SpeedTest client and retrieve client configuration from the server.
2. `STServerList`: To receive SpeedTest servers list from the server.
3. `STServerSorter`: To find best server based on Latency and Sort them.
4. `STDownloader`: To run download test with the given server-item.
5. `STUploader`: To run upload  test with the given server-item.
6. `STUploaderHttp`: To run upload test using http protocol.

## Example

There is an example project, in the `examples/speedtest/easytest` folder. It's a simple speedtest client, written using QtSpeedTest module.
You can run it by below command in the ubuntu:

```bash
/usr/lib/x86_64-linux-gnu/qt5/examples/speedtest/easytest/easytest
```

