# Each test is a small program that returns 0 on success and non-zero
# on failure. add_test() registers it with CTest.

add_executable(test_steady_state test_steady_state.cpp)
target_link_libraries(test_steady_state PRIVATE heat::heat)
add_test(NAME steady_state COMMAND test_steady_state)

add_executable(test_invalid_input test_invalid_input.cpp)
target_link_libraries(test_invalid_input PRIVATE heat::heat)
add_test(NAME invalid_input COMMAND test_invalid_input)

# Programs can also be tested by checking their output. Here the
# application itself is run and must print the line for t = 24 hours.
# The value is a regular expression: " +" matches one or more spaces.
add_test(NAME heat_rod_runs COMMAND heat_rod)
set_tests_properties(heat_rod_runs PROPERTIES PASS_REGULAR_EXPRESSION "t = +24\\.0 h")
