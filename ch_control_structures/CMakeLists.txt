add_executable(if_statement1 if_statement1.cpp)
add_executable(if_statement2 if_statement2.cpp)
add_executable(if_statement3 if_statement3.cpp)
add_executable(switch_statement switch_statement.cpp)

set_target_properties(
    if_statement1
    if_statement2
    if_statement3
    switch_statement
    PROPERTIES
    FOLDER "ch_control_structures"
)