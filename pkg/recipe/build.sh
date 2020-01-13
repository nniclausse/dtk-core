#!/bin/bash

if [[ -d build ]]; then
    rm -rf build
fi
mkdir build
cd build

if [[ "$c_compiler" == "gcc" ]]; then
  export PATH="${PATH}:${BUILD_PREFIX}/${HOST}/sysroot/usr/lib:${BUILD_PREFIX}/${HOST}/sysroot/usr/include"
fi

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
