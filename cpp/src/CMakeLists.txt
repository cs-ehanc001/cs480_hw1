add_library(Game_and_Logic STATIC Board_4x4.cpp search.cpp)
target_include_directories(Game_and_Logic PUBLIC ${TOP_DIR}/cpp/include)
target_link_libraries(Game_and_Logic common_properties)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} common_properties Game_and_Logic)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                 ${CMAKE_BINARY_DIR})
