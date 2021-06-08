enable_language(Fortran)

add_executable(cprog cprog.cpp multiply.f90)
target_link_libraries(cprog)
