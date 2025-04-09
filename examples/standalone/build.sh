#!/bin/bash
# Build script for the standalone TinyTest example

# Exit on error
set -e

echo "Building TinyTest standalone example"

# Create build directory
mkdir -p build
cd build

# Configure the project
echo "Configuring the project..."
cmake ..

# Build the project
echo "Building the project..."
cmake --build .

# Run the tests
echo "Running the tests..."
ctest --output-on-failure

echo "Standalone example has been built and tested successfully!" 