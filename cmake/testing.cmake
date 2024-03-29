function(register_test input_test_file test_name)
  set(TEST_BIN_DIR ${CMAKE_BINARY_DIR}/tests)

  add_executable(${test_name} ${input_test_file})

  target_link_libraries(${test_name} PRIVATE compiler_flags supple::core supple::testing Game_and_Logic)

  target_include_directories(${test_name} PRIVATE ${TOP_DIR}/cpp/include/)

  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_BIN_DIR})

  target_compile_features(${test_name} PUBLIC cxx_std_20)

  add_test(
    NAME ${test_name}
    COMMAND ${test_name}
    WORKING_DIRECTORY ${TEST_BIN_DIR})

endfunction()

function(test_handling)

  # make ctest give useful output to console on test failure
  list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure" "--progress")

  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp)
endfunction()
