# TinyTest Examples

This directory contains examples demonstrating how to use TinyTest in different build environments.

## Available Examples

### 1. Standalone Example

Located in the `standalone` directory, this example demonstrates:

- How to use TinyTest in a standalone project with CMake's FetchContent
- No pre-installation required - TinyTest is automatically downloaded and built
- Testing multiple functions: arithmetic, string manipulation, prime checking
- Collecting and reporting test results

[View the Standalone Example](./standalone/)

### 2. Preinstalled Example

Located in the `preinstalled` directory, this example demonstrates:

- How to use TinyTest when it's installed on the system
- Using CMake's find_package to locate the TinyTest installation
- Testing a simple calculator application with exception handling
- The build script automatically installs TinyTest if it's not found

[View the Preinstalled Example](./preinstalled/)

### 3. Sample Project

Located in the `sample_project` directory, this example demonstrates:

- A minimal example that tests a single function
- Complete build scripts for both Windows and Linux/macOS
- Clear structure for a small TinyTest project

[View the Sample Project](./sample_project/)

## Building the Examples

Each example includes its own build scripts and instructions. See the README.md file in each example directory for specific details.

### Quick Start

```bash
# For the standalone example
cd standalone
chmod +x build.sh  # On Linux/macOS
./build.sh         # On Linux/macOS
build.bat          # On Windows

# For the preinstalled example
cd preinstalled
chmod +x build.sh  # On Linux/macOS
./build.sh         # On Linux/macOS
build.bat          # On Windows

# For the sample project
cd sample_project
chmod +x build.sh  # On Linux/macOS
./build.sh         # On Linux/macOS
build.bat          # On Windows
```

## Choosing the Right Approach

- **Standalone (FetchContent)**: Best for projects where you want to ensure everyone has the same version of TinyTest without requiring a separate installation step.

- **Preinstalled (find_package)**: Best for larger projects or environments where TinyTest is a common dependency shared across multiple projects.

- **Sample Project**: Best for learning the basics of TinyTest with minimal complexity. 