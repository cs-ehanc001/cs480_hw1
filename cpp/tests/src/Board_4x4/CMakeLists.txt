register_test(constructor.cpp "Board_4x4_Constructor")
register_test(move_validity.cpp "Move_Validity")

add_executable(Printing_eye_test printing.cpp)
target_link_libraries(Printing_eye_test PRIVATE common_properties Game_and_Logic)
set_target_properties(Printing_eye_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
