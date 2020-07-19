#!/bin/sh

cd app
mkdir ../build
cd ../build
qmake ../app/spacebattle.pro
make

