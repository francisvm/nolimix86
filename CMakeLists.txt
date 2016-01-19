cmake_minimum_required(VERSION 2.8.12.2)

project(nolimix86)

# Use debug build type by default
set(CMAKE_BUILD_TYPE debug)

# Output all executables in build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Set the standard to C++14
# CMake < 3.1 doesn't support CMAKE_CXX_STANDARD.
if(${CMAKE_VERSION} VERSION_GREATER 3.0)
  set(CMAKE_CXX_STANDARD 14)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

# Enable more warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
# Force color output for ninja
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
# Disable RTTI
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

# llvm
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/llvm/build")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${PROJECT_SOURCE_DIR}/llvm/include")
find_package(LLVM REQUIRED CONFIG)
message(STATUS "LLVM version: ${LLVM_PACKAGE_VERSION} in ${LLVM_BUILD_BINARY_DIR}")
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Set the include path
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory("src")
add_subdirectory("tests")
