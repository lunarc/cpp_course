# ---------------------------------------------------------------------
# Example 01 - The smallest useful CMake project
#
# A single C++ source file is compiled into a single executable.
#
# Build (from this directory):
#
#   cmake -S . -B build          # configure: generate the build system
#   cmake --build build          # build: compile and link
#
# The executable ends up in build/ (or build/Debug/ with Visual Studio).
# ---------------------------------------------------------------------

# Every project starts by stating the oldest CMake version it supports.
# This also selects the default behaviour ("policies") of CMake.
cmake_minimum_required(VERSION 3.20)

# Name the project and the languages used. CMake now looks for a
# C++ compiler on your system.
project(Hello LANGUAGES CXX)

# The program uses std::println from <print>, which is part of C++23.
# Compilers default to an older standard, so we must ask for C++23.
set(CMAKE_CXX_STANDARD 23)

# Create an executable called "hello" from the source file hello.cpp.
add_executable(hello hello.cpp)
