@echo off
:: Build script for the standalone TinyTest example on Windows

echo Building TinyTest standalone example

:: Create build directory
if not exist build mkdir build
cd build

:: Configure the project
echo Configuring the project...
cmake ..

:: Build the project
echo Building the project...
cmake --build . --config Release

:: Run the tests
echo Running the tests...
ctest -C Release --output-on-failure

echo Standalone example has been built and tested successfully! 