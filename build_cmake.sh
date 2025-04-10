#!/bin/bash
# Helper script to build TinyTest with CMake

# Exit on error
set -e

# Create build directory if it doesn't exist
mkdir -p build_ci
cd build_ci

# Use the same CMake settings as in CI
cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DTINYTEST_BUILD_SHARED_LIBS=OFF \
  -DBUILD_TESTING=ON

# Build the project
cmake --build .

# Run tests
ctest --output-on-failure

echo "Build complete!"
echo "To run tests: cd build_ci && ctest"
echo "To install: cd build_ci && sudo cmake --install ." 