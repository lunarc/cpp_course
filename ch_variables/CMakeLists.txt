add_executable(int_types1 int_types1.cpp)
add_executable(int_types2 int_types2.cpp)
add_executable(char_types1 char_types1.cpp)
add_executable(double_types1 double_types1.cpp)
add_executable(numerical_limits numerical_limits.cpp)
add_executable(enum_types enum_types.cpp)
add_executable(class_enum class_enum.cpp)
add_executable(array_types1 array_types1.cpp)
add_executable(array_types2 array_types2.cpp)
add_executable(pointers1 pointers1.cpp)
add_executable(pointers2 pointers2.cpp)
add_executable(const_types const_types.cpp)
add_executable(reference_type reference_type.cpp)
add_executable(strucutured_type structured_type.cpp)
add_executable(var_auto1 auto1.cpp)
add_executable(var_auto2 auto2.cpp)

set_target_properties(
    int_types1
    int_types2
    char_types1
    double_types1
    numerical_limits
    enum_types
    class_enum
    array_types1
    array_types2
    pointers1
    pointers2
    const_types
    reference_type
    strucutured_type
    var_auto1
    var_auto2
    PROPERTIES
    FOLDER "ch_variables"
)
