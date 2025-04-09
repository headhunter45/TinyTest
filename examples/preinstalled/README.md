# TinyTest Preinstalled Example

This example demonstrates how to use TinyTest when it is installed on the system, integrating it through the CMake `find_package` mechanism.

## What This Example Demonstrates

- How to use a preinstalled TinyTest library with `find_package`
- How to create and run test suites for a simple calculator application
- How to test both regular function behavior and exception handling
- How to combine and report test results

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

## How It Works

1. The build script:
   - Checks if TinyTest is installed. If not, it builds and installs it
   - Creates a build directory
   - Configures the project with CMake, pointing to the TinyTest installation
   - Builds the project
   - Runs the tests with CTest

2. The CMake configuration:
   - Finds TinyTest with `find_package(TinyTest REQUIRED)`
   - Links the calculator test executable against `TinyTest::tinytest`
   - Registers the test with CTest

3. The test code:
   - Defines simple calculator functions
   - Creates test suites for each function
   - Executes the test suites and collects results
   - Tests exception handling for division by zero
   - Prints a summary of the results

## Code Structure

- `main.cpp`: Contains the calculator functions and tests
- `CMakeLists.txt`: Configures the build system to use the installed TinyTest
- `build.sh`/`build.bat`: Scripts to install TinyTest if needed, and build and run the example

## Understanding the Integration

The key part of the integration is in the CMakeLists.txt file:

```cmake
# Find TinyTest package
find_package(TinyTest REQUIRED)

# Link against the installed TinyTest library
target_link_libraries(calculator_test
  PRIVATE
    TinyTest::tinytest
)
```

This approach requires TinyTest to be installed on the system, either manually or through a package manager. The build script in this example will install TinyTest automatically if it's not found. 