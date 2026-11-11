# ---------------------------------------------------------------------
# Example 07 - Using a dependency found on the system: OpenMP
#
# find_package() searches the system for an installed package and
# creates *imported targets* for it (here OpenMP::OpenMP_CXX). Linking
# to an imported target adds the right compiler flags, include paths
# and libraries automatically - for every compiler.
#
# OpenMP ships with GCC, Clang (libomp may need installing) and MSVC,
# so this example normally works without installing anything.
#
#   cmake -S . -B build
#   cmake --build build --config Release
#
# The example also shows an *optional* dependency: if OpenMP is not
# found the program is still built, just without parallelism.
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(MonteCarloPi LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(mc_pi mc_pi.cpp)
target_compile_features(mc_pi PRIVATE cxx_std_23)

# Without REQUIRED, configuration continues even if OpenMP is missing.
# The variable OpenMP_CXX_FOUND tells us the outcome.
find_package(OpenMP)

if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP ${OpenMP_CXX_VERSION} found - building parallel version")
    target_link_libraries(mc_pi PRIVATE OpenMP::OpenMP_CXX)
else()
    message(WARNING "OpenMP not found - building serial version")
endif()

# --- A second dependency: the system thread library ---------------------
#
# std::thread needs -pthread on Linux. find_package(Threads) handles
# this portably; on Windows it simply does nothing.

find_package(Threads REQUIRED)

add_executable(mc_pi_threads mc_pi_threads.cpp)
target_compile_features(mc_pi_threads PRIVATE cxx_std_23)
target_link_libraries(mc_pi_threads PRIVATE Threads::Threads)
