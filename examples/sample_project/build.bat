@echo off
:: Build script for the sample project on Windows

:: Check if TinyTest is installed
if not exist "%USERPROFILE%\tinytest-install" (
  echo TinyTest is not installed in %USERPROFILE%\tinytest-install. Installing it now...
  
  :: Go to the root of the TinyTest project
  cd ..\..\
  
  :: Build and install TinyTest
  if not exist build mkdir build
  cd build
  cmake .. -DCMAKE_INSTALL_PREFIX=%USERPROFILE%\tinytest-install
  cmake --build . --config Release
  cmake --install . --config Release
  
  :: Return to the sample project directory
  cd ..\examples\sample_project
  
  echo TinyTest has been installed.
)

:: Create build directory
if not exist build mkdir build
cd build

:: Configure, build, and test the sample project
echo Configuring the project...
cmake .. -DCMAKE_PREFIX_PATH=%USERPROFILE%\tinytest-install

echo Building the project...
cmake --build . --config Release

echo Running the tests...
ctest -C Release --output-on-failure

echo Example project has been built and tested successfully! 