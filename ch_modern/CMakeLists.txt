add_executable(auto1 auto1.cpp)
add_executable(auto2 auto2.cpp)
add_executable(range_loops1 range_loops1.cpp)
add_executable(smart_pointers1 smart_pointers1.cpp)

set_target_properties(
    auto1
    auto2
    range_loops1
    smart_pointers1
    PROPERTIES
    FOLDER "ch_modern"
)