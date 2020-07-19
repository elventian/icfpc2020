#!/bin/sh

cd app
LD_LIBRARY_PATH=`pwd`
cd ../build
ldd qt_hello_world
./qt_hello_world "$@" || echo "run error code: $?"

