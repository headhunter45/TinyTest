cmake_minimum_required(VERSION 3.14)
project(TinyTestStandaloneExample VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# FetchContent for dependency management
include(FetchContent)

# Method 1: Use FetchContent to download TinyTest from GitHub
FetchContent_Declare(
  tinytest
  GIT_REPOSITORY https://github.com/headhunter45/TinyTest.git
  GIT_TAG main  # or a specific tag/commit
)

# Make TinyTest available
FetchContent_MakeAvailable(tinytest)

# Create the example executable
add_executable(tinytest_example 
  example.cpp
)

# Link against the TinyTest library
target_link_libraries(tinytest_example
  PRIVATE
    tinytest_lib
)

# Enable CTest
include(CTest)
enable_testing()
add_test(NAME example_test COMMAND tinytest_example) 