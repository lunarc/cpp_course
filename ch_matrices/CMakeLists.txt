add_executable(matrix1_eig matrix1_eig.cpp)
target_link_libraries(matrix1_eig PRIVATE Eigen3::Eigen)

add_executable(matrix2_eig matrix2_eig.cpp)
target_link_libraries(matrix2_eig PRIVATE Eigen3::Eigen)

add_executable(matrix3_eig matrix3_eig.cpp calfem_eig.h calfem_eig.cpp)
target_link_libraries(matrix3_eig PRIVATE Eigen3::Eigen)

add_executable(matrix4_eig matrix4_eig.cpp calfem_eig.h calfem_eig.cpp)
target_link_libraries(matrix4_eig PRIVATE Eigen3::Eigen)

add_executable(matrix5_eig matrix5_eig.cpp calfem_eig.h calfem_eig.cpp)
target_link_libraries(matrix5_eig PRIVATE Eigen3::Eigen)

add_executable(matrix_expressions_1 matrix_expressions_1.cpp)
target_link_libraries(matrix_expressions_1 PRIVATE Eigen3::Eigen)


set_target_properties(
    matrix1_eig
    matrix2_eig
    matrix3_eig
    matrix4_eig
    matrix5_eig
    matrix_expressions_1
    PROPERTIES
    FOLDER "ch_matrices"
)
