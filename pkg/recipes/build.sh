#!/bin/bash

if [[ -d build ]]; then
    rm -rf build
fi
mkdir build
cd build
if [ `uname` = "Darwin" ]; then
    cmake .. \
          -DCMAKE_INSTALL_PREFIX="${PREFIX}" \
          -DCMAKE_INSTALL_LIBDIR=lib \
          -DCMAKE_BUILD_TYPE=Release \
          -DZLIB_LIBRARY_RELEASE=$PREFIX/lib/libz.dylib
else
    cmake .. \
          -DCMAKE_INSTALL_PREFIX="${PREFIX}" \
          -DCMAKE_INSTALL_LIBDIR=lib \
          -DCMAKE_BUILD_TYPE=Release \
          -DZLIB_LIBRARY_RELEASE=$PREFIX/lib/libz.so
fi

make -j${CPU_COUNT}
make install
