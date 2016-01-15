cmake_minimum_required(VERSION 2.6)

# Setup the compilers
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

project(nolimix86)

# Use debug build type by default
set(CMAKE_BUILD_TYPE debug)

# Output all executables in build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Set the standard to C++14
set(CMAKE_CXX_STANDARD 14)
# Enable more warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
# Force color output for ninja
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
# Disable RTTI
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

# boost
find_package(Boost 1.58.0 REQUIRED COMPONENTS
  program_options
)

# llvm
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/llvm/build)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "LLVM version: ${LLVM_PACKAGE_VERSION} in ${LLVM_BUILD_BINARY_DIR}")
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Set the include path
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory("src")
add_subdirectory("tests")
