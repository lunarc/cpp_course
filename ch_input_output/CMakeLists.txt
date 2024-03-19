add_executable(io1 io1.cpp)
add_executable(io2 io2.cpp)
add_executable(io3 io3.cpp)
add_executable(iomanip1 iomanip1.cpp)
add_executable(iomanip2 iomanip2.cpp)
add_executable(files1 files1.cpp)
add_executable(files2 files2.cpp)
add_executable(files3 files3.cpp)
add_executable(files4 files4.cpp)
add_executable(files5 files5.cpp)
add_executable(files6 files6.cpp)
add_executable(files7 files7.cpp)
add_executable(files8 files8.cpp)
add_executable(files9 files9.cpp)
add_executable(files10 files10.cpp)

set_target_properties(
    io1 io2 io3 iomanip1 iomanip2 files1 files2 files3 files4 files5 files6 files7 files8 files9 files10
    PROPERTIES
    FOLDER "ch_input_output"
)