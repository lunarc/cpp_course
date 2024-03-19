add_executable(async1 async1.cpp)
add_executable(auto1 auto1.cpp)
add_executable(auto2 auto2.cpp)
add_executable(range_loops1 range_loops1.cpp)
add_executable(smart_pointers1 smart_pointers1.cpp)
add_executable(threads1 threads1.cpp)
add_executable(threads2 threads2.cpp)
add_executable(threads3 threads3.cpp)
add_executable(threads4 threads4.cpp)

set_target_properties(
    async1
    auto1
    auto2
    range_loops1
    smart_pointers1
    threads1
    threads2
    threads3
    threads4
    PROPERTIES
    FOLDER "ch_modern"
)