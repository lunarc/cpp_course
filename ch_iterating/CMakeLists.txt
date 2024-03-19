add_executable(while_statement while_statement.cpp)
add_executable(do_statement do_statement.cpp)
add_executable(for_statement for_statement.cpp)
add_executable(for_statement2 for_statement2.cpp)
add_executable(iteration_control iteration_control.cpp)

set_target_properties(
    while_statement
    do_statement
    for_statement
    for_statement2
    iteration_control
    PROPERTIES
    FOLDER "ch_iterating"
)