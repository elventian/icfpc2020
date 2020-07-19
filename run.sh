#!/bin/sh

cd build
./spacebattle "$@" || echo "run error code: $?"
