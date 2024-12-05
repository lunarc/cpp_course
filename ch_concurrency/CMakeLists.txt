set(CMAKE_CXX_STANDARD 23)

add_executable(threads0 threads0.cpp)
add_executable(threads1 threads1.cpp)
add_executable(threads2 threads2.cpp)
add_executable(threads3 threads3.cpp)
add_executable(threads4 threads4.cpp)
add_executable(threads5 threads5.cpp)
add_executable(async1 async1.cpp)


set_target_properties(
    threads0
    threads1
    threads2
    threads3
    threads4
    threads5
    async1
    PROPERTIES
    FOLDER "ch_concurrency"
)
