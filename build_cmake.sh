#!/bin/bash
# Helper script to build TinyTest with CMake

# Exit on error
set -e

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake .. $@

# Build
echo "Building..."
cmake --build .

echo "Build complete!"
echo "To run tests: cd build && ctest"
echo "To install: cd build && sudo cmake --install ." 