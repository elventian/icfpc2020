#!/bin/sh

echo "/lib/x86_64-linux-gnu/:"
ls -lah /lib/x86_64-linux-gnu | grep -i qtcore

echo "/usr/include/x86_64-linux-gnu/qt5/QtCore/:"
ls -lah /usr/include/x86_64-linux-gnu/qt5/QtCore/ | grep -i qcore

cd app
mkdir ../build
cd ../build
qmake ../app/qt_hello_world.pro
make

ldd qt_hello_world

