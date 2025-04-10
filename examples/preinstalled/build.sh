#!/bin/bash
# Build script for the preinstalled TinyTest example

# Exit on error
set -e

# Check if TinyTest is installed
if [ ! -d "$HOME/tinytest-install" ]; then
  echo "TinyTest is not installed. Installing it now..."
  
  # Store the current directory
  EXAMPLE_DIR=$(pwd)
  
  # Go to the root of the TinyTest project (assuming we're in examples/preinstalled)
  cd ../../
  
  # Build and install TinyTest
  mkdir -p build-install
  cd build-install
  cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/tinytest-install
  cmake --build .
  cmake --install .
  
  # Return to the example directory
  cd $EXAMPLE_DIR
  
  echo "TinyTest has been installed to $HOME/tinytest-install"
fi

echo "Building the preinstalled TinyTest example"

# Create build directory
mkdir -p build
cd build

# Configure the project with the path to the installed TinyTest
echo "Configuring the project..."
cmake .. -DCMAKE_PREFIX_PATH=$HOME/tinytest-install

# Build the project
echo "Building the project..."
cmake --build .

# Run the tests
echo "Running the tests..."
ctest --output-on-failure

echo "Preinstalled example has been built and tested successfully!" 