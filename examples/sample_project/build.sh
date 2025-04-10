#!/bin/bash
# Build script for the sample project

# Exit on error
set -e

# Define installation paths to check
TINYTEST_INSTALL_PATHS=("$HOME/tinytest-install" "$HOME/tinytest-verify")
TINYTEST_INSTALLED=false

# Check if TinyTest is installed in any of the potential locations
for INSTALL_PATH in "${TINYTEST_INSTALL_PATHS[@]}"; do
  if [ -d "$INSTALL_PATH" ]; then
    echo "Found TinyTest installation at $INSTALL_PATH"
    TINYTEST_PATH=$INSTALL_PATH
    TINYTEST_INSTALLED=true
    break
  fi
done

# Install TinyTest if not found
if [ "$TINYTEST_INSTALLED" = false ]; then
  echo "TinyTest is not installed. Installing it now..."
  
  # Store current directory
  EXAMPLE_DIR=$(pwd)
  
  # Go to the root of the TinyTest project
  cd ../../
  
  # Build and install TinyTest
  mkdir -p build
  cd build
  cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/tinytest-install
  cmake --build .
  cmake --install .
  
  # Return to the sample project directory
  cd $EXAMPLE_DIR
  
  echo "TinyTest has been installed."
  TINYTEST_PATH=$HOME/tinytest-install
fi

# Create build directory
mkdir -p build
cd build

# Configure, build, and test the sample project
echo "Configuring the project..."
cmake .. -DCMAKE_PREFIX_PATH=$TINYTEST_PATH

echo "Building the project..."
cmake --build .

echo "Running the tests..."
ctest --output-on-failure

echo "Example project has been built and tested successfully!" 