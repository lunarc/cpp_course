# ---------------------------------------------------------------------
# Example 13a - Installing a library so other projects can use it
#
# "Installing" copies the finished library, its headers and a small
# set of CMake files to a directory (the *install prefix*). Another
# project can then use the library with find_package(Materials),
# exactly like Eigen in example 08.
#
#   cmake -S . -B build
#   cmake --build build --config Release
#   cmake --install build --config Release --prefix ../install
#
# Resulting layout:
#
#   install/
#   ├── include/materials/materials.h
#   ├── lib/materials.lib  (or libmaterials.a)
#   └── lib/cmake/Materials/
#       ├── MaterialsConfig.cmake
#       ├── MaterialsConfigVersion.cmake
#       └── MaterialsTargets.cmake
#
# Then build the consumer project in ../consumer.
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(Materials VERSION 1.2.0 LANGUAGES CXX)

# Standard install directory names (lib, lib64, include, bin, ...)
# following the conventions of the platform.
include(GNUInstallDirs)

add_library(materials STATIC src/materials.cpp include/materials/materials.h)
add_library(Materials::materials ALIAS materials)

target_compile_features(materials PUBLIC cxx_std_23)

# The include directory differs between the build tree and the
# installed copy. BUILD_INTERFACE is used while building this project,
# INSTALL_INTERFACE (relative to the install prefix) by projects that
# use the installed library.
target_include_directories(materials PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# --- Installation rules ------------------------------------------------

# 1. The library itself. EXPORT records the target in an "export set"
#    that is written to a CMake file in step 3.
install(TARGETS materials
    EXPORT MaterialsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 2. The public headers.
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# 3. MaterialsTargets.cmake, which defines the imported target
#    Materials::materials for users of the installed library.
install(EXPORT MaterialsTargets
    NAMESPACE Materials::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Materials
)

# 4. MaterialsConfig.cmake (read by find_package) and
#    MaterialsConfigVersion.cmake (used to check version requirements
#    such as find_package(Materials 1.0)).
include(CMakePackageConfigHelpers)

configure_package_config_file(
    cmake/MaterialsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MaterialsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Materials
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MaterialsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MaterialsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MaterialsConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Materials
)
