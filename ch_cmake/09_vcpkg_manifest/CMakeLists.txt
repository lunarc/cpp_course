# ---------------------------------------------------------------------
# Example 09 - Letting a package manager provide the dependencies: vcpkg
#
# Installing libraries by hand on every computer is tedious. With
# vcpkg's *manifest mode* the dependencies are listed in vcpkg.json next
# to this file. When CMake is configured with the vcpkg toolchain file,
# vcpkg downloads and builds the listed packages automatically, and the
# usual find_package() calls find them.
#
# One-time setup of vcpkg:
#
#   git clone https://github.com/microsoft/vcpkg
#   ./vcpkg/bootstrap-vcpkg.sh          (or bootstrap-vcpkg.bat)
#   set the environment variable VCPKG_ROOT to the vcpkg directory
#
# Configure and build using the preset in CMakePresets.json:
#
#   cmake --preset vcpkg
#   cmake --build --preset release
#
# which is short for
#
#   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
#   cmake --build build --config Release
#
# The first configure takes a while because the packages are built.
# They are cached, so later builds (also of other projects) are fast.
#
# Note: nothing in this file mentions vcpkg. The same CMakeLists.txt
# works with libraries from apt, brew, conda or a manual install.
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(TrussSolver LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Eigen3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(truss truss.cpp)
target_compile_features(truss PRIVATE cxx_std_23)
target_link_libraries(truss PRIVATE Eigen3::Eigen nlohmann_json::nlohmann_json)

# The program reads its input from truss.json. Copy the file next to
# the executable after each build so the program can be run directly.
# $<TARGET_FILE_DIR:truss> is a *generator expression*: it is replaced
# by the directory of the executable at build time, which differs
# between generators (e.g. bin/ for Ninja, bin/Release/ for Visual Studio).
add_custom_command(TARGET truss POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/truss.json
            $<TARGET_FILE_DIR:truss>
    COMMENT "Copying truss.json to the output directory"
)
