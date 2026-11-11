# ---------------------------------------------------------------------
# Example 08 - Using an installed third-party library: Eigen
#
# Eigen is a widely used C++ library for linear algebra. Unlike OpenMP
# it is not part of the compiler, so it must be installed first, e.g.
#
#   Ubuntu/Debian : sudo apt install libeigen3-dev
#   macOS         : brew install eigen
#   conda         : conda install -c conda-forge eigen
#   vcpkg         : vcpkg install eigen3   (see also example 09)
#
# Packages installed in standard system locations are found
# automatically. Otherwise tell CMake where to look:
#
#   cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/eigen/install
#   cmake -S . -B build -DCMAKE_PREFIX_PATH=$CONDA_PREFIX
#
# or, when using vcpkg:
#
#   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
#
# Then build as usual:
#
#   cmake --build build --config Release
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(SpringChain LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# CONFIG: use the Eigen3Config.cmake file that Eigen installs.
# REQUIRED: stop with an error message if Eigen cannot be found.
# 3.3 is the minimum acceptable version.
find_package(Eigen3 3.3 CONFIG REQUIRED)

message(STATUS "Found Eigen ${Eigen3_VERSION} in ${Eigen3_DIR}")

add_executable(spring_chain spring_chain.cpp)
target_compile_features(spring_chain PRIVATE cxx_std_23)

# Eigen3::Eigen is an imported target defined by Eigen3Config.cmake.
# Eigen is header-only, so this only adds an include directory, but the
# syntax is the same as for any compiled library.
target_link_libraries(spring_chain PRIVATE Eigen3::Eigen)
