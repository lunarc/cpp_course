# ---------------------------------------------------------------------
# Example 02 - One executable built from several source files
#
# Real programs are split into several .cpp/.h files. All of them are
# listed in add_executable(). We also select the C++ standard and tell
# the compiler where to find our header files.
#
#   cmake -S . -B build
#   cmake --build build
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(Integrate VERSION 1.0 LANGUAGES CXX)

# Require C++23 for all targets in this project. Without REQUIRED,
# CMake would silently fall back to an older standard if the compiler
# lacks support.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # use -std=c++23, not -std=gnu++23

# All source files that make up the program. Header files are not
# compiled on their own, but listing them makes them show up in IDEs
# such as Visual Studio and Qt Creator.
add_executable(integrate
    src/main.cpp
    src/integration.cpp
    src/integration.h
    src/functions.cpp
    src/functions.h
)

# Directories searched for #include "..." files. PRIVATE means the
# setting only applies when compiling this target (more about
# PRIVATE/PUBLIC in the library examples).
target_include_directories(integrate PRIVATE src)
