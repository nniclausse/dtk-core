mkdir build
cd build

call conda activate dtk-core
set BUILD_CONFIG=Release
set CONDA_PREFIX=%CONDA_PREFIX%
set LIBRARY_LIB=%CONDA_PREFIX%\Library\lib
set LIBRARY_PREFIX=%CONDA_PREFIX%\Library

cmake .. -G "Visual Studio 16 2019" ^
-Wno-dev ^
-DCMAKE_INSTALL_PREFIX=%LIBRARY_PREFIX% ^
-DCMAKE_PREFIX_PATH=%LIBRARY_PREFIX% ^
-DCMAKE_INSTALL_RPATH:STRING=%LIBRARY_LIB% ^
-DCMAKE_INSTALL_NAME_DIR=%LIBRARY_LIB%

if errorlevel 1 echo "ERROR"

cmake --build . -j 4 --config %BUILD_CONFIG% --target install 

cd ..

if errorlevel 1 echo "ERROR 2"
