add_executable(strings1 strings1.cpp)
add_executable(strings2 strings2.cpp)
add_executable(strings3 strings3.cpp)
add_executable(strings4 strings4.cpp)
add_executable(strings5 strings5.cpp)

set_target_properties(
    strings1 strings2 strings3 strings4 strings5
    PROPERTIES
    FOLDER "ch_strings"
)