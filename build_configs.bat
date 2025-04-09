@echo off
:: Script to test different build configurations for TinyTest on Windows

echo Testing multiple build configurations for TinyTest

:: Function to build and test a configuration
:build_and_test
set build_dir=%~1
set cmake_args=%~2 %~3 %~4 %~5
echo.
echo Building in %build_dir% with args: %cmake_args%
echo.

if not exist %build_dir% mkdir %build_dir%
cd %build_dir%

:: Configure
echo Configuring...
cmake .. %cmake_args%

:: Build
echo Building...
cmake --build . --config Release

:: Test (if tests are enabled)
echo %cmake_args% | findstr "BUILD_TESTING=OFF" > nul
if %errorlevel% neq 0 (
  echo Testing...
  ctest -C Release --output-on-failure
)

cd ..
echo Successfully built and tested %build_dir%
echo.
exit /b 0

:: Clean build directories
echo Cleaning previous build directories...
if exist build-debug rmdir /s /q build-debug
if exist build-release rmdir /s /q build-release
if exist build-shared rmdir /s /q build-shared
if exist build-static rmdir /s /q build-static
if exist build-no-tests rmdir /s /q build-no-tests

:: Test debug build
call :build_and_test build-debug "-DCMAKE_BUILD_TYPE=Debug"

:: Test release build
call :build_and_test build-release "-DCMAKE_BUILD_TYPE=Release"

:: Test shared library build
call :build_and_test build-shared "-DCMAKE_BUILD_TYPE=Release" "-DTINYTEST_BUILD_SHARED_LIBS=ON"

:: Test static library build with no warnings as errors
call :build_and_test build-static "-DCMAKE_BUILD_TYPE=Release" "-DTINYTEST_BUILD_SHARED_LIBS=OFF" "-DTINYTEST_WARNINGS_AS_ERRORS=OFF"

:: Test build without tests
call :build_and_test build-no-tests "-DCMAKE_BUILD_TYPE=Release" "-DBUILD_TESTING=OFF"

echo All configurations built successfully! 