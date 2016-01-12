cmake_minimum_required(VERSION 2.6)

project(nolimia32)

# Use clang by default
set(CMAKE_CXX_COMPILER "clang++")

# Set the standard to C++14
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -fno-rtti -std=c++14")
set(CMAKE_CXX_STANDARD 14)

# boost
find_package(Boost 1.58.0 REQUIRED COMPONENTS
  program_options
)

# llvm
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/llvm/build)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Set the include path
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory("src")
add_subdirectory("tests")
