cmake_minimum_required(VERSION 3.14)
project(TinyTestPreinstalledExample VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find TinyTest package
find_package(TinyTest REQUIRED)

# Create the example executable
add_executable(calculator_test 
  main.cpp
)

# Link against the installed TinyTest library
target_link_libraries(calculator_test
  PRIVATE
    TinyTest::tinytest
)

# Enable CTest
include(CTest)
enable_testing()
add_test(NAME calculator_test COMMAND calculator_test) 