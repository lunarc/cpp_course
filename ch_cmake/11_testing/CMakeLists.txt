# ---------------------------------------------------------------------
# Example 11 - Unit testing with Catch2 and CTest
#
# Numerical code needs tests: does the integrator converge at the
# expected rate, does it handle edge cases? A test framework such as
# Catch2 makes writing such checks easy, and CTest runs them all.
#
#   cmake -S . -B build
#   cmake --build build --config Release
#   ctest --test-dir build -C Release --output-on-failure
#
# Catch2 is fetched with FetchContent (see example 10). Testing can be
# switched off with -DQUAD_BUILD_TESTS=OFF, which also avoids the
# download.
# ---------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(Quadrature VERSION 1.0 LANGUAGES CXX)

option(QUAD_BUILD_TESTS "Build the unit tests" ON)

# --- Library under test ---------------------------------------------

add_library(quadrature STATIC src/quadrature.cpp include/quadrature.h)
target_include_directories(quadrature PUBLIC include)
target_compile_features(quadrature PUBLIC cxx_std_23)

# --- Tests ------------------------------------------------------------

if(QUAD_BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(Catch2
        URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.1.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(test_quadrature tests/test_quadrature.cpp)

    # Catch2::Catch2WithMain provides main(), so the test file only
    # contains test cases.
    target_link_libraries(test_quadrature PRIVATE quadrature Catch2::Catch2WithMain)

    # catch_discover_tests() asks the test program which test cases it
    # contains and registers each of them as a separate CTest test.
    # Compared to a single add_test() this gives a clear report of
    # exactly which test case failed.
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(test_quadrature)
endif()
