add_executable(allocating_memory_modern allocating_memory.cpp)
add_executable(allocating_array_modern allocating_array.cpp)
add_executable(array_2d_modern array_2d.cpp)
add_executable(cont_array_2d_modern cont_array_2d.cpp)
add_executable(struct_array_modern struct_array.cpp)
add_executable(struct_array2_modern struct_array2.cpp)
add_executable(std_array1 std_array1.cpp)
add_executable(std_array2 std_array2.cpp)

set_target_properties(
    allocating_memory_modern
    allocating_array_modern
    array_2d_modern
    cont_array_2d_modern
    struct_array_modern
    struct_array2_modern
    std_array1
    std_array2
    PROPERTIES
    FOLDER "ch_arrays_modern"
)