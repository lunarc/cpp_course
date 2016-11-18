set(CMAKE_CXX_COMPILER /opt/local/bin/g++)
set(CMAKE_C_COMPILER /opt/local/bin/gcc)

project(hello)

add_executable(hello_world hello.cpp utils.cpp)
