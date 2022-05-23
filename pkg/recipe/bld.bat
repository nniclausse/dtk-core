@echo off

mkdir build
cd build

set BUILD_CONFIG=Release

cmake ..  ^
    -Wno-dev ^
    -DCMAKE_INSTALL_PREFIX=%LIBRARY_PREFIX% ^
    -DCMAKE_PREFIX_PATH=%LIBRARY_PREFIX% ^
    -DCMAKE_INSTALL_RPATH:STRING=%LIBRARY_LIB% ^
    -DCMAKE_INSTALL_NAME_DIR=%LIBRARY_LIB%

if errorlevel 1 exit 1

cmake --build . --config %BUILD_CONFIG% --target install
if errorlevel 1 exit 1
