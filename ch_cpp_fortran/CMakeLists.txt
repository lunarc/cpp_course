enable_language(Fortran)

add_executable(cprog cprog.cpp multiply.f90)

set_target_properties(
    cprog
    PROPERTIES
    FOLDER "ch_cpp_fortran"
)