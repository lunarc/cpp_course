cmake_minimum_required(VERSION 3.0)

# set(CMAKE_C_COMPILER /opt/local/bin/gcc)
# set(CMAKE_CXX_COMPILER /opt/local/bin/g++)



project(cpp_course C CXX)

if (WIN32)
    if (MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_USE_MATH_DEFINES /DARMA_USE_LAPACK /DARMA_USE_BLAS")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_USE_MATH_DEFINES /DARMA_USE_LAPACK /DARMA_USE_BLAS")
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if (WIN32)
	include_directories( armadillo/include )
else()
	include_directories( armadillo/include )

#	find_package(PythonLibs)
#	include_directories (${PYTHON_INCLUDE_DIRS})

#	find_package(Boost 1.45.0 COMPONENTS python)
#	include_directories (${Boost_INCLUDE_DIRS})
endif()

if (WIN32)
        subdirs(ch_arrays ch_control_structures ch_data_structures
               ch_functions ch_input_output ch_iterating ch_matrices ch_oop ch_operators ch_strings ch_variables ch_vector_and_lists ch_threads)
else()
        subdirs(ch_arrays ch_control_structures ch_cpp_fortran ch_data_structures
               ch_functions ch_input_output ch_iterating ch_matrices ch_oop ch_operators ch_strings ch_variables ch_vector_and_lists)
endif()
