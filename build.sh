#!/bin/sh

ls -lah /lib/x86_64-linux-gnu | grep -i qtcore

cd app
mkdir ../build
cd ../build
qmake ../app/qt_hello_world.pro
make

ldd qt_hello_world

