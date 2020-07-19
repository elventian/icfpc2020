#!/bin/sh

cd app
mkdir ../build
g++ -std=c++11 -fPIC -lQt5Core -I/usr/include/x86_64-linux-gnu/qt5/QtCore/ -I/usr/include/x86_64-linux-gnu/qt5/ -o ../build/main main.cpp
