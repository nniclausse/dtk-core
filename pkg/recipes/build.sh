#!/bin/bash

if [[ -d build ]]; then
    rm -rf build
fi
mkdir build
cd build
cmake .. \
      -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DCMAKE_INSTALL_LIBDIR=lib

make -j${CPU_COUNT}
make install
