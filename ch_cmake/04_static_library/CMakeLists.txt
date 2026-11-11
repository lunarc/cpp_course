# ---------------------------------------------------------------------
# Example 04 - Building and using a static library
#
# Code that is used by several programs is best put in a library. The
# library is compiled once and then linked into each program.
#
#   cmake -S . -B build
#   cmake --build build
#
# Key ideas:
#   add_library()              creates a library target
#   target_link_libraries()    makes a program use a library
#   PUBLIC / PRIVATE           controls what is passed on to users
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(StatsDemo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- The library -----------------------------------------------------

# STATIC: the object code is copied into each program at link time.
# The result is libstats.a (Linux/macOS/MinGW) or stats.lib (MSVC).
add_library(stats STATIC
    stats/src/descriptive.cpp
    stats/src/regression.cpp
    stats/include/stats/descriptive.h
    stats/include/stats/regression.h
)

# Users of the library write #include <stats/descriptive.h>, so they
# need stats/include on their include path. PUBLIC means: use this
# directory when compiling the library itself AND pass it on to every
# target that links to the library.
target_include_directories(stats PUBLIC stats/include)

# Instead of setting CMAKE_CXX_STANDARD globally we state that this
# library needs C++23. Because it is PUBLIC, programs linking to stats
# are compiled with (at least) C++23 as well.
target_compile_features(stats PUBLIC cxx_std_23)

# --- Programs using the library -------------------------------------

add_executable(describe apps/describe.cpp)
add_executable(fit_line apps/fit_line.cpp)

# Linking to stats automatically gives the programs the include
# directory and C++ standard declared PUBLIC above. No need to repeat
# them here - this is what "modern", target-based CMake is about.
target_link_libraries(describe PRIVATE stats)
target_link_libraries(fit_line PRIVATE stats)
