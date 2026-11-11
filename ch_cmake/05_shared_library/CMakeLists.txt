# ---------------------------------------------------------------------
# Example 05 - Building a shared (dynamic) library
#
# A shared library (.so on Linux, .dylib on macOS, .dll on Windows) is
# loaded when the program starts instead of being copied into it.
#
#   cmake -S . -B build                          # shared (default here)
#   cmake -S . -B build -DBUILD_SHARED_LIBS=OFF  # static instead
#   cmake --build build
#
# Two practical issues show up with shared libraries:
#
# 1. On Windows, functions must be explicitly exported from a DLL.
#    CMake's GenerateExportHeader module writes a header with the
#    right macro (ODE_EXPORT) for every compiler.
#
# 2. The program must find the library at run time. On Windows the DLL
#    has to be in the same directory as the .exe (or on PATH), so we
#    put both in build/bin.
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(OdeDemo VERSION 1.0 LANGUAGES CXX)

# BUILD_SHARED_LIBS is a standard CMake variable. When ON, every
# add_library() without an explicit STATIC/SHARED becomes shared.
# option() makes it a switch that the user can change with -D.
option(BUILD_SHARED_LIBS "Build libraries as shared libraries" ON)

# Place executables and DLLs (RUNTIME) in the same directory so that
# Windows finds the DLL. LIBRARY = .so/.dylib, ARCHIVE = .lib/.a
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- The library -----------------------------------------------------

add_library(ode
    ode/src/solvers.cpp
    ode/include/ode/solvers.h
)

target_include_directories(ode PUBLIC
    ode/include
    ${CMAKE_CURRENT_BINARY_DIR}   # location of the generated ode_export.h
)

target_compile_features(ode PUBLIC cxx_std_23)

# Hide all symbols by default on Linux/macOS, the same behaviour as on
# Windows. Only functions marked ODE_EXPORT are visible to users.
set_target_properties(ode PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    VERSION ${PROJECT_VERSION}            # libode.so.1.0
    SOVERSION ${PROJECT_VERSION_MAJOR}    # libode.so.1
)

# Generates build/ode_export.h containing the ODE_EXPORT macro.
include(GenerateExportHeader)
generate_export_header(ode)

# --- Program -----------------------------------------------------------

add_executable(oscillator apps/oscillator.cpp)
target_link_libraries(oscillator PRIVATE ode)
