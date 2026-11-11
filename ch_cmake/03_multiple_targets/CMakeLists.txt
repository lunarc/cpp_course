# ---------------------------------------------------------------------
# Example 03 - Several executables in one project
#
# A typical scientific workflow has several small programs, e.g. one
# that generates data and one that analyses it. Each add_executable()
# creates a separate *target*. You can build all of them, or just one:
#
#   cmake -S . -B build
#   cmake --build build                    # build all targets
#   cmake --build build --target analyse   # build only "analyse"
#
# Two programs share random_walk.cpp. Here it is simply compiled
# twice. Example 04 shows how a library avoids this.
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(RandomWalk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put all executables in build/bin instead of scattering them over the
# build tree. This makes them easier to find and run.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Program 1: simulate random walks and write final positions to a file.
add_executable(simulate simulate.cpp random_walk.cpp random_walk.h)

# Program 2: read the file and compute statistics.
add_executable(analyse analyse.cpp)

# Program 3: a quick self-check of the random walk code.
add_executable(check_walk check_walk.cpp random_walk.cpp random_walk.h)

# Settings are applied per target. Here we turn on compiler warnings
# for all three programs. Compilers use different flags, so we check
# which one is in use.
foreach(target IN ITEMS simulate analyse check_walk)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endforeach()
