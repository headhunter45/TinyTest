# TinyTest Example Project

This is a sample project that demonstrates how to use TinyTest in a CMake project.

## Prerequisites

- CMake 3.14 or higher
- C++17 compatible compiler
- TinyTest installed (the build script will install it if needed)

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

## How it Works

1. The build script:
   - Checks if TinyTest is installed. If not, it builds and installs it
   - Creates a build directory
   - Configures the project with CMake
   - Builds the project
   - Runs the tests with CTest

2. The CMake configuration:
   - Finds TinyTest with `find_package(TinyTest REQUIRED)`
   - Links the example test executable against `TinyTest::tinytest`
   - Registers the test with CTest

3. The test code:
   - Includes the TinyTest header
   - Defines a test suite using TinyTest's API
   - Runs the tests and reports results

## Understanding the Code

The main.cpp file demonstrates:
- How to define a function to test
- How to create test suites
- How to define tests with expected output
- How to execute test suites
- How to print and interpret test results 