# ---------------------------------------------------------------------
# Example 13b - Using the installed Materials library
#
# This is a completely separate project. It knows nothing about the
# source code of the library, only where it was installed:
#
#   cmake -S . -B build -DCMAKE_PREFIX_PATH=<path to>/13_install_and_export/install
#   cmake --build build --config Release
#
# CMAKE_PREFIX_PATH is a list of directories where find_package()
# looks for installed packages.
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(MaterialTable LANGUAGES CXX)

# Requires version 1.x of the library, x >= 0 (see SameMajorVersion in
# the library's CMakeLists.txt).
find_package(Materials 1.0 CONFIG REQUIRED)

message(STATUS "Found Materials ${Materials_VERSION} in ${Materials_DIR}")

add_executable(material_table main.cpp)
target_link_libraries(material_table PRIVATE Materials::materials)
