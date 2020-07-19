#!/bin/sh

cd app
mkdir ../build
cd ../build
qmake ../app/qt_hello_world.pro
make

