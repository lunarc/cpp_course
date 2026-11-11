# ---------------------------------------------------------------------
# Example 10 - Downloading a dependency with FetchContent
#
# FetchContent downloads the source code of a dependency while CMake
# configures the project and builds it as part of your own project.
# Nothing has to be installed beforehand - only an internet connection
# is needed the first time.
#
# Good for small libraries and for making a project easy to build for
# others. For large libraries (Qt, VTK, Boost, ...) a package manager or
# a system install (examples 08 and 09) is usually a better choice.
#
# Here we fetch CLI11, a library for parsing command-line arguments,
# so that simulation parameters can be given without recompiling:
#
#   cmake -S . -B build
#   cmake --build build --config Release
#   build/bin/projectile --help
#   build/bin/projectile --speed 50 --angle 30 --drag 0.01
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(Projectile LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# Describe where to get the dependency. Always pin an exact version
# (a release tag or commit), never a moving branch such as "main",
# so that the build is reproducible.
#
# Downloading a release archive is faster than cloning with git. The
# git alternative would be:
#
#   FetchContent_Declare(cli11
#       GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
#       GIT_TAG        v2.4.2
#       GIT_SHALLOW    TRUE
#   )
FetchContent_Declare(cli11
    URL https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.4.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Download (first time only) and add the dependency to the build. After
# this call the targets defined by CLI11 are available.
FetchContent_MakeAvailable(cli11)

add_executable(projectile projectile.cpp)
target_compile_features(projectile PRIVATE cxx_std_23)
target_link_libraries(projectile PRIVATE CLI11::CLI11)
