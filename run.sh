#!/bin/sh

cd build
./qt_hello_world "$@" || echo "run error code: $?"
