cmake_minimum_required(VERSION 3.10)

# set(CMAKE_C_COMPILER /opt/local/bin/gcc)
# set(CMAKE_CXX_COMPILER /opt/local/bin/g++)

project(cpp_course C CXX)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 20)

if (WIN32)
        subdirs(ch_arrays ch_arrays_modern ch_control_structures ch_data_structures ch_qt
               ch_functions ch_input_output ch_iterating ch_matrices ch_oop ch_operators ch_strings ch_variables ch_vector_and_lists ch_threads)
else()
        subdirs(ch_arrays ch_arrays_modern ch_control_structures ch_cpp_fortran ch_data_structures ch_modern ch_qt
               ch_functions ch_input_output ch_iterating ch_matrices ch_oop ch_operators ch_strings ch_variables ch_vector_and_lists)
endif()
