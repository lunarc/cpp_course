# ---------------------------------------------------------------------
# Example 14 - Mixing C++ and Fortran in one project
#
# Much scientific software is written in Fortran. CMake supports
# Fortran as a first-class language, so C++ and Fortran sources can be
# combined in the same project, even in the same target.
#
# A Fortran compiler is required (gfortran, Intel ifx, flang, ...).
# Visual Studio's C++ compiler can be combined with Intel ifx; with
# MinGW or on Linux/macOS gfortran works out of the box:
#
#   cmake -S . -B build
#   cmake --build build
#
# On Windows with MinGW (e.g. the one that ships with Qt):
#
#   cmake -S . -B build -G "MinGW Makefiles"
#   cmake --build build
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

# Enabling Fortran makes CMake look for a Fortran compiler.
project(TridiagonalSolver LANGUAGES CXX Fortran)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# The Fortran code is put in its own library. CMake picks the right
# compiler for each file based on the extension (.f90 -> Fortran).
add_library(tridiag STATIC fortran/tridiag.f90)

# Fortran modules (.mod files) are written to this directory.
set_target_properties(tridiag PROPERTIES
    Fortran_MODULE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/modules
)

# Unlike the other examples this one uses C++20 and std::cout instead
# of C++23 std::print: Fortran toolchains such as MinGW gfortran often
# come with a GCC older than 14, which lacks <print>.
add_executable(cable cpp/cable.cpp cpp/tridiag.h)
target_compile_features(cable PRIVATE cxx_std_20)
# The executable is linked by the C++ compiler, which does not know
# about the Fortran runtime library (libgfortran, ...). CMake sees that
# tridiag contains Fortran code and adds the runtime automatically.
target_link_libraries(cable PRIVATE tridiag)
