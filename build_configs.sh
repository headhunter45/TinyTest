#!/bin/bash
# Script to test different build configurations for TinyTest

set -e  # Exit on error

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
BOLD='\033[1m'
NC='\033[0m' # No Color

echo -e "${BOLD}Testing multiple build configurations for TinyTest${NC}\n"

# Function to build and test a configuration
build_and_test() {
  local build_dir="$1"
  local cmake_args="${@:2}"  # All arguments except the first one
  
  echo -e "${BLUE}Building in ${build_dir} with args: ${cmake_args}${NC}"
  
  mkdir -p "${build_dir}"
  cd "${build_dir}"
  
  # Configure
  echo -e "${BOLD}Configuring...${NC}"
  cmake .. ${cmake_args}
  
  # Build
  echo -e "${BOLD}Building...${NC}"
  cmake --build .
  
  # Test (if tests are enabled)
  if [[ "${cmake_args}" != *"BUILD_TESTING=OFF"* ]]; then
    echo -e "${BOLD}Testing...${NC}"
    ctest --output-on-failure
  fi
  
  cd ..
  echo -e "${GREEN}Successfully built and tested ${build_dir}${NC}\n"
}

# Clean build directories
echo "Cleaning previous build directories..."
rm -rf build-debug build-release build-shared build-static build-no-tests

# Test debug build
build_and_test "build-debug" "-DCMAKE_BUILD_TYPE=Debug"

# Test release build
build_and_test "build-release" "-DCMAKE_BUILD_TYPE=Release"

# Test shared library build
build_and_test "build-shared" "-DCMAKE_BUILD_TYPE=Release" "-DTINYTEST_BUILD_SHARED_LIBS=ON"

# Test static library build with no warnings as errors
build_and_test "build-static" "-DCMAKE_BUILD_TYPE=Release" "-DTINYTEST_BUILD_SHARED_LIBS=OFF" "-DTINYTEST_WARNINGS_AS_ERRORS=OFF"

# Test build without tests
build_and_test "build-no-tests" "-DCMAKE_BUILD_TYPE=Release" "-DBUILD_TESTING=OFF"

echo -e "${GREEN}${BOLD}All configurations built successfully!${NC}" 