set(CMAKE_CXX_STANDARD 23)

add_executable(threads0 threads0.cpp)
add_executable(threads1 threads1.cpp)
add_executable(threads1_algo threads1_algo.cpp)
add_executable(threads2 threads2.cpp)
add_executable(threads3 threads3.cpp)
add_executable(threads4 threads4.cpp)
add_executable(threads5 threads5.cpp)
add_executable(threads6 threads6.cpp)
add_executable(async1 async1.cpp)
add_executable(async2 async2.cpp)
add_executable(halo_eigen1 halo_eigen1.cpp)
add_executable(producer_consumer safe_queue.h producer_consumer.cpp)
add_executable(par_algo1 par_algo1.cpp)
add_executable(par_algo2 par_algo2.cpp)
add_executable(par_algo3 par_algo3.cpp)
add_executable(par_for_each1 par_for_each1.cpp)
add_executable(par_transform1 par_transform1.cpp)


set_target_properties(
    threads0
    threads1
    threads1_algo
    threads2
    threads3
    threads4
    threads5
    threads6
    async1
    async2
    producer_consumer
    par_algo1
    par_algo2
    par_algo3
    par_for_each1
    par_transform1
    halo_eigen1
    PROPERTIES
    FOLDER "ch_concurrency"
)
