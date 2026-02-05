set(CMAKE_CXX_STANDARD 23)

include(CheckCXXSourceCompiles)

# Check for support of C++ parallel algorithms (std::execution policies)
set(CMAKE_REQUIRED_FLAGS "${CMAKE_CXX_FLAGS}")
check_cxx_source_compiles("#include <execution>\n#include <vector>\n#include <algorithm>\nint main(){ std::vector<int> v(1); std::for_each(std::execution::par, v.begin(), v.end(), [](int&){ }); return 0; }" HAVE_STD_EXECUTION)

find_package(OpenMP)

add_executable(threads0 threads0.cpp)
add_executable(threads1 threads1.cpp)
add_executable(threads2 threads2.cpp)
add_executable(threads3 threads3.cpp)
add_executable(threads4 threads4.cpp)
add_executable(threads5 threads5.cpp)
add_executable(threads6 threads6.cpp)
add_executable(async1 async1.cpp)
add_executable(async2 async2.cpp)

# The OpenMP-dependent example is added only when OpenMP is available
if(OpenMP_CXX_FOUND)
    add_executable(halo_eigen1 halo_eigen1.cpp)
    target_link_libraries(halo_eigen1 PRIVATE OpenMP::OpenMP_CXX)
else()
    message(WARNING "OpenMP not found — skipping ch_concurrency/halo_eigen1. Install libomp (Homebrew: brew install libomp) to enable it.")
endif()

add_executable(producer_consumer safe_queue.h producer_consumer.cpp)

# Add parallel-algorithm examples only if the standard library provides them
if(HAVE_STD_EXECUTION)
    add_executable(threads1_algo threads1_algo.cpp)
    add_executable(par_algo1 par_algo1.cpp)
    add_executable(par_algo2 par_algo2.cpp)
    add_executable(par_algo3 par_algo3.cpp)
    add_executable(par_for_each1 par_for_each1.cpp)
    add_executable(par_transform1 par_transform1.cpp)
else()
    message(WARNING "C++ parallel algorithms (std::execution) not supported by this compiler/stdlib — skipping related examples.")
endif()


set(CONCURRENCY_TARGETS
    threads0
    threads1
    threads2
    threads3
    threads4
    threads5
    threads6
    async1
    async2
    producer_consumer
)

if (TARGET halo_eigen1)
    list(APPEND CONCURRENCY_TARGETS halo_eigen1)
endif()
if (TARGET threads1_algo)
    list(APPEND CONCURRENCY_TARGETS threads1_algo)
endif()
if (TARGET par_algo1)
    list(APPEND CONCURRENCY_TARGETS par_algo1)
endif()
if (TARGET par_algo2)
    list(APPEND CONCURRENCY_TARGETS par_algo2)
endif()
if (TARGET par_algo3)
    list(APPEND CONCURRENCY_TARGETS par_algo3)
endif()
if (TARGET par_for_each1)
    list(APPEND CONCURRENCY_TARGETS par_for_each1)
endif()
if (TARGET par_transform1)
    list(APPEND CONCURRENCY_TARGETS par_transform1)
endif()

set_target_properties(${CONCURRENCY_TARGETS} PROPERTIES FOLDER "ch_concurrency")
