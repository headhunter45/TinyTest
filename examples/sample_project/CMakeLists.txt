cmake_minimum_required(VERSION 3.14)
project(TinyTestExample VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Debug: Print CMAKE_PREFIX_PATH before finding package
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

# Find TinyTest package
find_package(TinyTest REQUIRED)

# Debug: Print variables after finding TinyTest
message(STATUS "TinyTest found: ${TinyTest_FOUND}")
message(STATUS "TinyTest include dirs: ${TINYTEST_INCLUDE_DIRS}")
message(STATUS "TinyTest libraries: ${TINYTEST_LIBRARIES}")

# Create an example executable that uses TinyTest
add_executable(example_test
  main.cpp
)

# Configure include directories explicitly
target_include_directories(example_test
  PRIVATE
    ${TINYTEST_INCLUDE_DIRS}
)

# Link against TinyTest
target_link_libraries(example_test
  PRIVATE
    TinyTest::tinytest
)

# Add a test using CTest
include(CTest)
enable_testing()
add_test(NAME example_test COMMAND example_test) 