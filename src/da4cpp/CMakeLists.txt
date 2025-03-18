################
# da4cpp/graph #
################
add_library(graph graph.cpp)
target_include_directories(graph PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(graph PRIVATE default_project_cxx_flags)

##################
# da4cpp/parsing #
##################
add_library(parsing parsing.cpp)
target_include_directories(parsing PRIVATE ${LLVM_INCLUDE_DIRS})
target_include_directories(parsing PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_definitions(parsing PRIVATE ${LLVM_DEFINITIONS})
target_link_libraries(parsing PRIVATE libclang graph default_project_cxx_flags)
# da4cpp/parsing.tests
add_executable(parsing_tests parsing.tests.cpp)
target_compile_definitions(parsing_tests PRIVATE TEST_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(parsing_tests PRIVATE Catch2::Catch2WithMain parsing default_project_cxx_flags)
configure_file(parsing.tests.resources/function_call.cpp parsing.tests.resources/function_call.cpp)
configure_file(
  parsing.tests.resources/struct_reference.cpp parsing.tests.resources/struct_reference.cpp
)
configure_file(
  parsing.tests.resources/struct_forward_declaration.cpp
  parsing.tests.resources/struct_forward_declaration.cpp
)
catch_discover_tests(parsing_tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
