cmake_minimum_required(VERSION 3.12)

project(particles)

find_package(Python 3.6 REQUIRED)
find_package(Boost 1.64.0 REQUIRED COMPONENTS system)

include_directories(/sw/easybuild/software/MPI/GCC/6.4.0-2.28/OpenMPI/2.1.2/Python/3.6.4/include/python3.6m)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(/sw/easybuild/software/MPI/GCC/6.4.0-2.28/OpenMPI/2.1.2/Boost.Python/1.66.0-Python-3.6.4/include)

add_library(particle SHARED mymodule1.cpp)
target_link_libraries(particle ${Boost_LIBRARIES} boost_python3)

set_target_properties(particle PROPERTIES PREFIX "")

