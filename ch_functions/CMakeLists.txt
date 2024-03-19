add_executable(array_functions array_functions.cpp)
add_executable(functions1 functions1.cpp)
add_executable(functions2 functions2.cpp)
add_executable(functions3 functions3.cpp)
add_executable(functions4 functions4.cpp)
add_executable(functions5 functions5.cpp)
add_executable(functions6 functions6.cpp)
add_executable(functions7 functions7.cpp)
add_executable(functions8 functions8.cpp)
add_executable(array_functions2 array_functions2.cpp)
add_executable(header_files array_utils.h array_utils.cpp header_files.cpp)
add_executable(header_files2 array_utils2.h array_utils2.cpp
header_files2.cpp)

set_target_properties(
    array_functions
    functions1
    functions2
    functions3
    functions4
    functions5
    functions6
    functions7
    functions8
    array_functions2
    header_files
    header_files2
    PROPERTIES
    FOLDER "ch_functions"
)