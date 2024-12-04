cmake_minimum_required(VERSION 3.20)

# set(CMAKE_C_COMPILER /opt/local/bin/gcc)
# set(CMAKE_CXX_COMPILER /opt/local/bin/g++)

project(cpp_course C CXX) 

option(BUILD_QT_EXAMPLES "Build Qt examples" ON)
option(BUILD_VTK_EXAMPLES "Build VTK examples" OFF)
option(BUILD_EIGEN_EXAMPLES "Build Eigen examples" ON)
option(BUILD_MIXED_LANG_EXAMPLES "Build mixed language examples" OFF)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 20)

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
