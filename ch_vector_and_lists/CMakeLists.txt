add_executable(vectors1 vectors1.cpp)
add_executable(vectors2 vectors2.cpp)
add_executable(vectors3 vectors3.cpp)

set_target_properties(
    vectors1
    vectors2
    vectors3
    PROPERTIES
    FOLDER "ch_vectors_and_lists"
)
