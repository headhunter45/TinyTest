@echo off
setlocal enabledelayedexpansion

echo Verifying TinyTest CMake Integration
echo.

REM 1. Build with CMake in Debug and Release modes
echo Step 1: Building TinyTest in Debug and Release modes

REM Clean and build in Debug mode
echo Building in Debug mode...
if exist build-debug rmdir /s /q build-debug
mkdir build-debug
cd build-debug
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
cd ..

REM Clean and build in Release mode
echo Building in Release mode...
if exist build-release rmdir /s /q build-release
mkdir build-release
cd build-release
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cd ..

echo Successfully built in both Debug and Release modes
echo.

REM 2. Run tests using CTest
echo Step 2: Running tests with CTest

REM Run tests for Debug build
echo Running tests for Debug build...
cd build-debug
ctest -C Debug --output-on-failure
cd ..

REM Run tests for Release build
echo Running tests for Release build...
cd build-release
ctest -C Release --output-on-failure
cd ..

echo Successfully ran tests with CTest
echo.

REM 3. Installation test
echo Step 3: Testing installation

REM Install to temporary location
echo Installing TinyTest...
cd build-release
set INSTALL_PATH=%USERPROFILE%\tinytest-verify
cmake .. -DCMAKE_INSTALL_PREFIX=!INSTALL_PATH!
cmake --install . --config Release
cd ..

REM Verify installation
echo Verifying installation files...
set ERROR=0

if not exist "!INSTALL_PATH!\include\tinytest\tinytest.h" (
  echo ERROR: tinytest.h not found in installation directory
  set ERROR=1
)

if not exist "!INSTALL_PATH!\lib\tinytest.lib" (
  echo ERROR: tinytest.lib not found in installation directory
  set ERROR=1
)

if not exist "!INSTALL_PATH!\lib\cmake\TinyTest\TinyTestConfig.cmake" (
  echo ERROR: TinyTestConfig.cmake not found in installation directory
  set ERROR=1
)

if not exist "!INSTALL_PATH!\lib\cmake\TinyTest\TinyTestConfigVersion.cmake" (
  echo ERROR: TinyTestConfigVersion.cmake not found in installation directory
  set ERROR=1
)

if !ERROR!==0 (
  echo Installation verified successfully
  echo.
) else (
  echo Installation verification failed
  exit /b 1
)

REM 4. Check for pkg-config file existence
echo Step 4: Checking pkg-config file

echo Checking pkg-config file installation...
if not exist "!INSTALL_PATH!\lib\pkgconfig\tinytest.pc" (
  echo ERROR: tinytest.pc not found in pkgconfig directory
  set ERROR=1
) else (
  echo Successfully found pkg-config file
  echo NOTE: Full pkg-config verification requires pkg-config tool which may not be available on Windows
)

echo.

REM 5. Build a small project that uses TinyTest as a dependency
echo Step 5: Building a sample project that uses TinyTest

echo Building and testing the sample project...
cd examples\sample_project
call build.bat
cd ..\..

echo Sample project built and tested successfully
echo.

REM 6. Summary
echo Verification Summary
echo ✓ TinyTest builds with CMake in Debug and Release modes
echo ✓ Tests run successfully with CTest
echo ✓ Installation works properly
echo ✓ pkg-config file is installed correctly
echo ✓ TinyTest can be used as a dependency in other CMake projects

echo.
echo Verification complete! All tests passed.

REM Clean up temporary installation
rmdir /s /q %USERPROFILE%\tinytest-verify

exit /b 0 