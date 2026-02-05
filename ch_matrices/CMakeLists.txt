find_package(OpenMP)

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

add_executable(matrix_reshape_1 matrix_reshape_1.cpp)
target_link_libraries(matrix_reshape_1 PRIVATE Eigen3::Eigen)

add_executable(matrix_slicing_1 matrix_slicing_1.cpp)
target_link_libraries(matrix_slicing_1 PRIVATE Eigen3::Eigen)

add_executable(matrix_solver_1 matrix_solver_1.cpp)
target_link_libraries(matrix_solver_1 PRIVATE Eigen3::Eigen)

add_executable(matrix_solver_2 matrix_solver_2.cpp)
target_link_libraries(matrix_solver_2 PRIVATE Eigen3::Eigen)

add_executable(matrix_solver_3 matrix_solver_3.cpp)
target_link_libraries(matrix_solver_3 PRIVATE Eigen3::Eigen)

add_executable(matrix_solver_4 matrix_solver_4.cpp)
target_link_libraries(matrix_solver_4 PRIVATE Eigen3::Eigen)

add_executable(eigen_c_arrays1 eigen_c_arrays1.cpp)
target_link_libraries(eigen_c_arrays1 PRIVATE Eigen3::Eigen)


if(OpenMP_CXX_FOUND)
    # Build the OpenMP examples when OpenMP is available
    add_executable(matrix_openmp_1 matrix_openmp_1.cpp)
    target_link_libraries(matrix_openmp_1 PRIVATE Eigen3::Eigen OpenMP::OpenMP_CXX)

    add_executable(matrix_openmp_2 matrix_openmp_2.cpp)
    target_link_libraries(matrix_openmp_2 PRIVATE Eigen3::Eigen OpenMP::OpenMP_CXX)

    # Suppress Eigen deprecation warnings coming from system headers on compilers
    # that warn about deprecated std:: features (e.g. AppleClang libc++).
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "AppleClang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(matrix_openmp_1 PRIVATE -Wno-deprecated-declarations)
        target_compile_options(matrix_openmp_2 PRIVATE -Wno-deprecated-declarations)
    elseif(MSVC)
        target_compile_options(matrix_openmp_1 PRIVATE /wd4996)
        target_compile_options(matrix_openmp_2 PRIVATE /wd4996)
    endif()
else()
    message(WARNING "OpenMP not found — skipping matrix_openmp examples. Install libomp (Homebrew: brew install libomp) to enable them.")
endif()

set(MATRIX_TARGETS
    matrix1_eig
    matrix2_eig
    matrix3_eig
    matrix4_eig
    matrix5_eig
    matrix_expressions_1
    matrix_reshape_1
    matrix_slicing_1
    matrix_solver_1
    matrix_solver_2
    matrix_solver_3
    matrix_solver_4
    eigen_c_arrays1
)

if (TARGET matrix_openmp_1)
    list(APPEND MATRIX_TARGETS matrix_openmp_1)
endif()
if (TARGET matrix_openmp_2)
    list(APPEND MATRIX_TARGETS matrix_openmp_2)
endif()

set_target_properties(${MATRIX_TARGETS} PROPERTIES FOLDER "ch_matrices")
