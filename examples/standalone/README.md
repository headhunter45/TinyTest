# TinyTest Standalone Example

This example demonstrates how to use TinyTest in a standalone project using CMake's FetchContent to automatically download and build TinyTest.

## What This Example Demonstrates

- How to use CMake's FetchContent to automatically download TinyTest
- How to create test suites for different types of functions
- How to define test cases with expected results
- How to execute tests and collect the results

## Prerequisites

- CMake 3.14 or higher
- C++17 compatible compiler
- Git (for FetchContent to download TinyTest)

## Building and Running

### On Linux/macOS

```bash
# Make the build script executable
chmod +x build.sh

# Run the build script
./build.sh
```

### On Windows

```batch
build.bat
```

## How It Works

1. CMake is configured to use FetchContent to download TinyTest
2. The example executable is linked against the TinyTest library
3. CTest is enabled to run the tests
4. Several functions are defined and tested:
   - `add`: Adds two integers
   - `concatenate`: Concatenates two strings
   - `isPrime`: Checks if a number is prime
   - `vectorSum`: Calculates the sum of a vector of integers

## Code Structure

- `example.cpp`: Contains the functions to test and test suites
- `CMakeLists.txt`: Configures the build system with FetchContent
- `build.sh`/`build.bat`: Scripts to build and run the example

## Understanding the Integration

The key part of the integration is in the CMakeLists.txt file:

```cmake
# Use FetchContent to download TinyTest
FetchContent_Declare(
  tinytest
  GIT_REPOSITORY https://github.com/headhunter45/TinyTest.git
  GIT_TAG main
)

# Make TinyTest available
FetchContent_MakeAvailable(tinytest)

# Link against the TinyTest library
target_link_libraries(tinytest_example
  PRIVATE
    tinytest_lib
)
```

This approach automatically downloads, builds, and links against TinyTest without requiring a separate installation step. 