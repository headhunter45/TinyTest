@echo off
setlocal enabledelayedexpansion

REM Create build directory if it doesn't exist
if not exist build_ci mkdir build_ci
cd build_ci

REM Use the same CMake settings as in CI
cmake .. ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DTINYTEST_BUILD_SHARED_LIBS=OFF ^
  -DBUILD_TESTING=ON

REM Build the project
cmake --build . --config Debug

REM Run tests
ctest -C Debug --output-on-failure

echo "Build complete!"
echo "To run tests: cd build_ci && ctest -C Debug"
echo "To install: cd build_ci && cmake --install . --config Debug" 