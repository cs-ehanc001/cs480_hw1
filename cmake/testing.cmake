function(add_test input_test_file)
  # remove parent directory path and extension
  get_filename_component(filename ${input_test_file} NAME_WLE)
  get_filename_component(raw_path ${input_test_file} DIRECTORY)

  string(REGEX REPLACE ".*/cpp/tests/src/" "" shortened_path ${raw_path})

  string(REPLACE "/" "_" nearly_corrected_path ${shortened_path})
  string(REGEX REPLACE "^_" "" corrected_path ${nearly_corrected_path})

  foreach(numeric_standard ${TEST_STANDARDS})
    set(test_exe_name ${corrected_path}_${filename}_${numeric_standard})

    add_executable(${test_exe_name} ${input_test_file})

    target_link_libraries(${test_exe_name} PRIVATE compiler_flags)

    target_include_directories(${test_exe_name} PRIVATE ${TOP_DIR}/cpp/include/)

    set_target_properties(${test_exe_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                      ${TEST_BIN_DIR})

    target_compile_features(${test_exe_name} PUBLIC cxx_std_${numeric_standard})

    # remove test_ prefix for prettier test output
    string(REPLACE "test_" "" test_name ${test_exe_name})

    add_test(
      NAME ${test_name}
      COMMAND ${test_exe_name}
      WORKING_DIRECTORY ${TEST_BIN_DIR})
  endforeach()

endfunction()

function(test_handling)
  set(TEST_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/tests)

  # make ctest give useful output to console on test failure
  list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure" "--progress")

  list(APPEND TEST_STANDARDS "20")

endfunction()
