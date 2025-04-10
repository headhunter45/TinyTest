# TinyTest

TinyTest is a lightweight C++ testing framework designed to simplify unit testing, with focus on ease of use and flexibility.

## Key Features

- Simple API for creating and running test suites
- Support for test setup and teardown functions
- Custom comparison functions for complex objects
- Detailed test results reporting
- Ability to skip tests conditionally
- Integration with CMake build system

## Examples

Several examples demonstrating how to use TinyTest in different environments are provided in the [examples/](examples/) directory:

1. **Standalone Example**: Uses CMake's FetchContent to automatically download TinyTest
2. **Preinstalled Example**: Uses find_package to locate a system-installed TinyTest
3. **Sample Project**: Minimal example showing basic TinyTest usage

Each example includes detailed instructions for building and running on both Windows and Linux/macOS systems.

## Building with CMake

TinyTest can be built using CMake:

```bash
# Create a build directory
mkdir build && cd build

# Configure
cmake ..

# Build
cmake --build .

# Run tests
ctest
```

## Usage Overview

Here's a simple example of how to use TinyTest:

```cpp
#include <tinytest/tinytest.h>

// Function to test
int add(int a, int b) {
    return a + b;
}

int main() {
    // Create a test suite
    auto suite = TinyTest::MakeTestSuite(
        "AddFunction",
        add,
        {
            TinyTest::MakeTest("should add two positive numbers", 
                5,               // Expected result
                std::make_tuple(2, 3))  // Input parameters
        }
    );
    
    // Execute the suite and get results
    auto results = TinyTest::ExecuteSuite(suite);
    
    // Print results
    TinyTest::PrintResults(std::cout, results);
    
    return (results.Failed() > 0 || results.Errors() > 0) ? 1 : 0;
}
```

## Integration Options

TinyTest can be integrated into your project in multiple ways:

1. **Using FetchContent** - automatically downloads and builds TinyTest
2. **Using find_package** - uses a pre-installed version of TinyTest
3. **Direct inclusion** - directly adding TinyTest as source files

See the [examples/](examples/) directory for detailed instructions on each approach.

## License

TinyTest is released under the MIT License. See [LICENSE](LICENSE) file for details.
