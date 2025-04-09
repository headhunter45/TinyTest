cmake_minimum_required(VERSION 3.14)
project(TinyTest VERSION 1.0.0 LANGUAGES CXX)

# Check for required C++ features
include(CheckCXXSourceCompiles)
include(CheckIncludeFileCXX)

# Check for C++17 support
set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -std=c++17")
check_cxx_source_compiles("
  #include <optional>
  #include <string_view>
  #include <tuple>
  #include <functional>
  int main() {
    std::optional<int> opt;
    std::string_view sv = \"test\";
    std::tuple<int, double> t{1, 2.0};
    return 0;
  }
" HAVE_CPP17_FEATURES)

if(NOT HAVE_CPP17_FEATURES)
  message(FATAL_ERROR "Your compiler doesn't support required C++17 features")
endif()

# Check for required headers
check_include_file_cxx(cstdint HAVE_CSTDINT)
check_include_file_cxx(functional HAVE_FUNCTIONAL)
check_include_file_cxx(optional HAVE_OPTIONAL)
check_include_file_cxx(string_view HAVE_STRING_VIEW)
check_include_file_cxx(tuple HAVE_TUPLE)
check_include_file_cxx(iostream HAVE_IOSTREAM)
check_include_file_cxx(sstream HAVE_SSTREAM)
check_include_file_cxx(vector HAVE_VECTOR)
check_include_file_cxx(utility HAVE_UTILITY)

if(NOT (HAVE_CSTDINT AND HAVE_FUNCTIONAL AND HAVE_OPTIONAL AND HAVE_STRING_VIEW AND
        HAVE_TUPLE AND HAVE_IOSTREAM AND HAVE_SSTREAM AND HAVE_VECTOR AND HAVE_UTILITY))
  message(FATAL_ERROR "Your standard library doesn't have all required headers")
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setup build configurations
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Configure compiler-specific flags for different build types
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Base flags
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter")
  # Debug specific
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
  # Release specific
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
  # Common error handling
  option(TINYTEST_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)
  if(TINYTEST_WARNINGS_AS_ERRORS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
  endif()
elseif(MSVC)
  # Base flags
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4100")
  # Debug specific - enable iterator debugging
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG")
  # Release specific
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
  # Common error handling
  option(TINYTEST_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)
  if(TINYTEST_WARNINGS_AS_ERRORS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
  endif()
endif()

# Show build configuration
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "C++ Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C++ Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")

# Options for build configuration
option(TINYTEST_BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TESTING "Build tests" ON)
option(TINYTEST_USE_SYSTEM_CPPUTILS "Use system-installed CPPUtils instead of downloading" OFF)

# Library type (static or shared)
if(TINYTEST_BUILD_SHARED_LIBS)
  set(TINYTEST_LIBRARY_TYPE SHARED)
  message(STATUS "Building shared libraries")
else()
  set(TINYTEST_LIBRARY_TYPE STATIC)
  message(STATUS "Building static libraries")
endif()

# Include FetchContent for dependencies
include(FetchContent)

# Handle CPPUtils dependency
if(NOT TINYTEST_USE_SYSTEM_CPPUTILS)
  # Disable CPPUtils tests to avoid conflicts with our targets
  set(CPPUTILS_BUILD_TESTS OFF CACHE BOOL "Disable CPPUtils tests" FORCE)
  set(CPPUTILS_ENABLE_TESTING OFF CACHE BOOL "Disable CPPUtils testing framework" FORCE)
  
  FetchContent_Declare(
    cpputils
    GIT_REPOSITORY https://github.com/headhunter45/cpp-utils.git
    GIT_TAG e75c0ed9cb86c1a1e1ee842f2f0240b07178ed10
  )
  
  # Customize CPPUtils integration to avoid conflicts
  FetchContent_GetProperties(cpputils)
  if(NOT cpputils_POPULATED)
    FetchContent_Populate(cpputils)
    
    # Set variables to prevent conflicts before we include the CMakeLists.txt
    set(CPPUTILS_BUILD_TESTS OFF CACHE BOOL "Disable CPPUtils tests" FORCE)
    set(CPPUTILS_BUILD_EXAMPLES OFF CACHE BOOL "Disable CPPUtils examples" FORCE)
    set(CPPUTILS_ENABLE_TESTING OFF CACHE BOOL "Disable CPPUtils testing framework" FORCE)
    
    # Store original flags
    set(CMAKE_CXX_FLAGS_ORIG ${CMAKE_CXX_FLAGS})
    
    # Add flags to disable specific warnings for template code
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
      # GCC
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      # Clang
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
    elseif(MSVC)
      # MSVC
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4100")
    endif()
    
    # Disable testing before adding cpputils
    set(BUILD_TESTING OFF CACHE BOOL "Disable testing for cpputils" FORCE)
    
    # Add the source directory but exclude everything from the default build
    add_subdirectory(${cpputils_SOURCE_DIR} ${cpputils_BINARY_DIR} EXCLUDE_FROM_ALL)
    
    # Restore original flags for our own code
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_ORIG})
  endif()
else()
  # Try to find system-installed CPPUtils
  find_package(CPPUtils REQUIRED)
endif()

# Re-enable testing for TinyTest
set(BUILD_TESTING ON CACHE BOOL "Enable testing for TinyTest" FORCE)

# Include testing support - AFTER cpputils is added
include(CTest)
enable_testing()

# TinyTest library - renamed to avoid conflicts
add_library(tinytest_lib ${TINYTEST_LIBRARY_TYPE}
  tinytest.cpp
)

# Set the output name to "tinytest" regardless of target name
set_target_properties(tinytest_lib PROPERTIES
  OUTPUT_NAME tinytest
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Get the CPPUtils source directory for includes
if(NOT TINYTEST_USE_SYSTEM_CPPUTILS)
  set(CPPUTILS_INCLUDE_DIR ${cpputils_SOURCE_DIR}/src)
else()
  # Try to find the include directory for system-installed CPPUtils
  find_path(CPPUTILS_INCLUDE_DIR pretty_print.h PATH_SUFFIXES cpputils)
endif()

target_include_directories(tinytest_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CPPUTILS_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Link against CPPUtils - using the correct target name
# Note: The actual target name might be different (pretty_print or cpputils)
target_link_libraries(tinytest_lib
  PRIVATE
    pretty_print
)

# Handle GoogleTest dependency
if(BUILD_TESTING)
  # Define our own custom tests list to avoid conflicts
  set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
  
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  # Get GoogleTest include directories
  FetchContent_GetProperties(googletest)
  set(GTEST_INCLUDE_DIRS 
    ${googletest_SOURCE_DIR}/googletest/include
    ${googletest_SOURCE_DIR}/googlemock/include
  )

  # Create test executable - renamed to avoid conflicts
  add_executable(tinytest_tests
    tinytest_test.cpp
  )

  # Set the output name to "tinytest_test" regardless of target name
  set_target_properties(tinytest_tests PROPERTIES
    OUTPUT_NAME tinytest_test
  )

  # Add include directories for tests
  target_include_directories(tinytest_tests
    PRIVATE
      ${CPPUTILS_INCLUDE_DIR}
      ${GTEST_INCLUDE_DIRS}
  )

  # Link against TinyTest library and GoogleTest
  target_link_libraries(tinytest_tests
    PRIVATE
      tinytest_lib
      GTest::gtest_main
      GTest::gmock
  )

  # Register test with CTest - make sure only our test is registered
  add_test(NAME tinytest_test COMMAND tinytest_tests)
  
  # Explicitly set the test list to prevent picking up other tests
  set_property(GLOBAL PROPERTY TEST_INCLUDE_FILES "")
endif()

# Installation
include(GNUInstallDirs)

# Install the library binary without export (due to dependencies)
install(TARGETS tinytest_lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tinytest
)

# Install the header file
install(FILES
  tinytest.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tinytest
)

# Create and install package configuration files
include(CMakePackageConfigHelpers)

# Generate the package configuration file
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/TinyTestConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/TinyTestConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TinyTest
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/TinyTestConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

# Install the configuration files
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/TinyTestConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/TinyTestConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TinyTest
)

# Generate and install pkg-config file
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinytest.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/tinytest.pc
  @ONLY
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/tinytest.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
) 