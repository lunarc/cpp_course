# ---------------------------------------------------------------------
# Example 12 - Build types, options, generated headers and presets
#
# This example collects techniques for controlling *how* a project is
# built:
#
#   * Debug / Release build types and a sensible default
#   * option() switches that change the code being compiled
#   * configure_file() to pass information from CMake into C++
#   * compiler warnings using generator expressions
#   * CMakePresets.json to store common configurations
#
# Single-configuration generators (Makefiles, Ninja) choose the build
# type when configuring:
#
#   cmake -S . -B build-debug   -DCMAKE_BUILD_TYPE=Debug
#   cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
#
# Multi-configuration generators (Visual Studio, Xcode, Ninja
# Multi-Config) choose it when building:
#
#   cmake -S . -B build
#   cmake --build build --config Release
#
# With presets (see CMakePresets.json; requires Ninja):
#
#   cmake --list-presets
#   cmake --preset release
#   cmake --build --preset release
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(Lorenz
    VERSION 2.1.0
    DESCRIPTION "Lorenz attractor integrator"
    LANGUAGES CXX
)

# --- Default build type ------------------------------------------------
#
# With a single-configuration generator and no CMAKE_BUILD_TYPE, the
# code is compiled without optimisation AND without debug info - the
# worst of both worlds for scientific codes. Default to Release.
get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT is_multi_config AND NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, defaulting to Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# --- User options ------------------------------------------------------

option(LORENZ_USE_FLOAT "Use single precision instead of double" OFF)
option(LORENZ_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# A cache variable with a fixed set of allowed values.
set(LORENZ_INTEGRATOR "rk4" CACHE STRING "Time integration method")
set_property(CACHE LORENZ_INTEGRATOR PROPERTY STRINGS euler rk4)

set(allowed_integrators euler rk4)
if(NOT LORENZ_INTEGRATOR IN_LIST allowed_integrators)
    message(FATAL_ERROR "LORENZ_INTEGRATOR must be euler or rk4, not '${LORENZ_INTEGRATOR}'")
endif()

# Print the configuration so it is visible in the configure output.
message(STATUS "Lorenz ${PROJECT_VERSION}")
message(STATUS "  Single precision : ${LORENZ_USE_FLOAT}")
message(STATUS "  Integrator       : ${LORENZ_INTEGRATOR}")

# --- Generated header --------------------------------------------------
#
# configure_file() copies config.h.in to the build directory, replacing
# @VARIABLE@ with the value of the CMake variable and #cmakedefine
# lines with #define or a comment depending on whether the variable is
# set. The C++ code can then print its version, settings, etc.

if(LORENZ_INTEGRATOR STREQUAL "rk4")
    set(LORENZ_USE_RK4 ON)
endif()

configure_file(src/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/generated/config.h)

# --- The program -------------------------------------------------------

add_executable(lorenz src/main.cpp)
target_compile_features(lorenz PRIVATE cxx_std_23)
target_include_directories(lorenz PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)

# An alternative to the generated header: pass a preprocessor
# definition directly on the compiler command line (-DNAME=value).
target_compile_definitions(lorenz PRIVATE
    LORENZ_BUILD_TYPE="$<IF:$<CONFIG:Debug>,Debug,Release>"
)

# --- Compiler warnings -------------------------------------------------
#
# Generator expressions $<...> are evaluated when the build system is
# generated. $<CXX_COMPILER_ID:MSVC> is 1 for MSVC and 0 otherwise, so
# each compiler gets only the flags it understands.
target_compile_options(lorenz PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Wconversion>
)

if(LORENZ_WARNINGS_AS_ERRORS)
    # From CMake 3.24 the target property COMPILE_WARNING_AS_ERROR
    # does the same thing.
    target_compile_options(lorenz PRIVATE
        $<IF:$<CXX_COMPILER_ID:MSVC>,/WX,-Werror>
    )
endif()
