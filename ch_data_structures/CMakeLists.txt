add_executable(lambda1 lambda1.cpp)
add_executable(lambda2 lambda2.cpp)
add_executable(lambda3 lambda3.cpp)
add_executable(lambda4 lambda4.cpp)
add_executable(lambda5 lambda5.cpp)
add_executable(vector1 vector1.cpp)
add_executable(vector2 vector2.cpp)
add_executable(vector3 vector3.cpp)
add_executable(vector4 vector4.cpp)
add_executable(deque1 deque1.cpp)
add_executable(list1 list1.cpp)
add_executable(map1 map1.cpp)
add_executable(operations1 operations1.cpp)
add_executable(algo1 algo1.cpp)
add_executable(algo2 algo2.cpp)
add_executable(algo3 algo3.cpp)
add_executable(copy1 copy1.cpp)
add_executable(fill1 fill1.cpp)
add_executable(numeric1 numeric1.cpp)
add_executable(transform1 transform1.cpp)
add_executable(remove1 remove1.cpp)
add_executable(ranges1 ranges1.cpp)

set_target_properties(
    lambda1
    lambda2
    lambda3
    lambda4
    lambda5
    vector1
    vector2
    vector3
    vector4
    deque1
    list1
    map1
    operations1
    algo1
    algo2
    algo3
    copy1
    fill1
    numeric1
    transform1
    remove1
    ranges1
    PROPERTIES
    FOLDER "ch_data_structures"
)