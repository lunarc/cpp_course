# ---------------------------------------------------------------------
# Example 06 - Organising a larger project in subdirectories
#
# As a project grows, one CMakeLists.txt becomes hard to read. Each
# directory can have its own CMakeLists.txt, included with
# add_subdirectory(). A common layout is:
#
#   06_project_structure/
#   ├── CMakeLists.txt        <- top level: project settings
#   ├── libs/heat/            <- reusable library code
#   │   ├── CMakeLists.txt
#   │   ├── include/heat/
#   │   └── src/
#   ├── apps/                 <- programs using the library
#   │   └── CMakeLists.txt
#   └── tests/                <- automatic tests run with ctest
#       └── CMakeLists.txt
#
#   cmake -S . -B build
#   cmake --build build --config Release
#   ctest --test-dir build -C Release      # run the tests
#
# (-C Release / --config Release are needed for multi-configuration
#  generators such as Visual Studio, and are ignored otherwise.)
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(HeatEquation VERSION 0.1 LANGUAGES CXX)

# A user-visible switch. Turn off with -DHEAT_BUILD_TESTS=OFF.
# Prefixing options with the project name avoids clashes when this
# project is used inside another one.
option(HEAT_BUILD_TESTS "Build the unit tests" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Order matters: the library must be defined before targets that link
# to it are created in later subdirectories.
add_subdirectory(libs/heat)
add_subdirectory(apps)

if(HEAT_BUILD_TESTS)
    # enable_testing() must be called in the top-level CMakeLists.txt,
    # otherwise ctest will not find any tests.
    enable_testing()
    add_subdirectory(tests)
endif()
