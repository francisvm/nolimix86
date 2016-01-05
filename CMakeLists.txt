cmake_minimum_required(VERSION 2.6)

project(nolimia32)

# Use clang by default
set(CMAKE_CXX_COMPILER "clang++")

# Set the standard to C++14
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -std=c++14")
set(CMAKE_CXX_STANDARD 14)

# boost
find_package(Boost 1.58.0 REQUIRED COMPONENTS
  program_options
)

# Set the include path
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory("src")
add_subdirectory("tests")
