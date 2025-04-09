@echo off
:: Helper script to build TinyTest with CMake on Windows

:: Create build directory if it doesn't exist
if not exist build mkdir build
cd build

:: Configure with CMake
echo Configuring with CMake...
cmake .. %*

:: Build
echo Building...
cmake --build . --config Release

echo Build complete!
echo To run tests: cd build ^&^& ctest -C Release
echo To install: cd build ^&^& cmake --install . --config Release 