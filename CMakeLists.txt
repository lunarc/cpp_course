cmake_minimum_required(VERSION 3.20)

# Autodetect vcpkg if not already configured
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  # Check common vcpkg installation locations
  if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
    message(STATUS "Using vcpkg from VCPKG_ROOT: $ENV{VCPKG_ROOT}")
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
    message(STATUS "Using vcpkg from project directory")
  elseif(WIN32)
    # Check common Windows locations
    if(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
      set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
          CACHE STRING "Vcpkg toolchain file")
      message(STATUS "Using vcpkg from C:/vcpkg")
    elseif(EXISTS "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")
      set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake"
          CACHE STRING "Vcpkg toolchain file")
      message(STATUS "Using vcpkg from E:/vcpkg")
    endif()
  elseif(UNIX)
    # Check common Unix/Linux locations
    if(EXISTS "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake")
      set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake"
          CACHE STRING "Vcpkg toolchain file")
      message(STATUS "Using vcpkg from home directory")
    elseif(EXISTS "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
      set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake"
          CACHE STRING "Vcpkg toolchain file")
      message(STATUS "Using vcpkg from /opt/vcpkg")
    endif()
  endif()
  
  if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(WARNING "vcpkg toolchain file not found. Please set VCPKG_ROOT environment variable or CMAKE_TOOLCHAIN_FILE.")
  endif()
endif()

# set(CMAKE_C_COMPILER /opt/local/bin/gcc)
# set(CMAKE_CXX_COMPILER /opt/local/bin/g++)

project(cpp_course C CXX) 

option(BUILD_QT_EXAMPLES "Build Qt examples" ON)
option(BUILD_VTK_EXAMPLES "Build VTK examples" OFF)
option(BUILD_EIGEN_EXAMPLES "Build Eigen examples" ON)
option(BUILD_MIXED_LANG_EXAMPLES "Build mixed language examples" ON)
option(BUILD_PYBIND11_EXAMPLES "Build pybind11 Python binding examples" ON)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(MSVC)
  SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
ENDIF()

if (BUILD_EIGEN_EXAMPLES)
  find_package(Eigen3 CONFIG REQUIRED)
endif()

if (BUILD_QT_EXAMPLES)
  if (LINUX)
    find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
  else()
    find_package(Qt6 CONFIG REQUIRED)
  endif()
endif()

#find_package(VTK REQUIRED)
#include("${VTK_USE_FILE}")

if (BUILD_VTK_EXAMPLES)
  find_package(VTK REQUIRED)
  include("${VTK_USE_FILE}")
  add_subdirectory(ch_vtk)
endif()

add_subdirectory(ch_arrays)
add_subdirectory(ch_arrays_modern)
add_subdirectory(ch_control_structures)

#add_subdirectory(ch_cpp_fortran)
add_subdirectory(ch_data_structures)
add_subdirectory(ch_modern)

if (BUILD_QT_EXAMPLES)
  add_subdirectory(ch_qt)
endif()

add_subdirectory(ch_functions)
add_subdirectory(ch_input_output)
add_subdirectory(ch_iterating)
add_subdirectory(ch_matrices)
add_subdirectory(ch_oop)
add_subdirectory(ch_operators)
add_subdirectory(ch_strings)
add_subdirectory(ch_variables)
add_subdirectory(ch_vector_and_lists)
add_subdirectory(ch_concurrency)
add_subdirectory(ch_mixed_language)
