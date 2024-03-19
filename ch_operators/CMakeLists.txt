add_executable(operators1 operators1.cpp)
add_executable(operators2 operators2.cpp)
add_executable(operators3 operators3.cpp)

set_target_properties(
    operators1
    operators2
    operators3
    PROPERTIES
    FOLDER "ch_operators"
)
