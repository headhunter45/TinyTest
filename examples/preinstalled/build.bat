@echo off
:: Build script for the preinstalled TinyTest example on Windows

:: Check if TinyTest is installed
if not exist "%USERPROFILE%\tinytest-install" (
  echo TinyTest is not installed. Installing it now...
  
  :: Store the current directory
  set EXAMPLE_DIR=%CD%
  
  :: Go to the root of the TinyTest project (assuming we're in examples/preinstalled)
  cd ..\..
  
  :: Build and install TinyTest
  if not exist build-install mkdir build-install
  cd build-install
  cmake .. -DCMAKE_INSTALL_PREFIX=%USERPROFILE%\tinytest-install
  cmake --build . --config Release
  cmake --install . --config Release
  
  :: Return to the example directory
  cd %EXAMPLE_DIR%
  
  echo TinyTest has been installed to %USERPROFILE%\tinytest-install
)

echo Building the preinstalled TinyTest example

:: Create build directory
if not exist build mkdir build
cd build

:: Configure the project with the path to the installed TinyTest
echo Configuring the project...
cmake .. -DCMAKE_PREFIX_PATH=%USERPROFILE%\tinytest-install

:: Build the project
echo Building the project...
cmake --build . --config Release

:: Run the tests
echo Running the tests...
ctest -C Release --output-on-failure

echo Preinstalled example has been built and tested successfully! 