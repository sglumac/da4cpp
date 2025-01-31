find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

add_library(graph graph.cpp)
target_include_directories(graph PUBLIC ${CMAKE_SOURCE_DIR})

add_library(parsing parsing.cpp)
target_include_directories(parsing PRIVATE ${LLVM_INCLUDE_DIRS})
target_include_directories(parsing PUBLIC ${CMAKE_SOURCE_DIR})
target_compile_definitions(parsing PRIVATE ${LLVM_DEFINITIONS})
target_link_libraries(parsing libclang graph)

add_executable(parsing_tests parsing.tests.cpp)
target_compile_definitions(parsing_tests PRIVATE TEST_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(parsing_tests PRIVATE Catch2::Catch2WithMain parsing)
configure_file(parsing.tests.resources/function_call.cpp parsing.tests.resources/function_call.cpp)
configure_file(parsing.tests.resources/struct_reference.cpp parsing.tests.resources/struct_reference.cpp)
configure_file(parsing.tests.resources/cyclic_struct_dependency.cpp parsing.tests.resources/cyclic_struct_dependency.cpp)
catch_discover_tests(parsing_tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(da4cpp lib.cpp)
target_link_libraries(da4cpp graph parsing)

add_executable(da4cpp_app main.cpp)
target_link_libraries(da4cpp_app da4cpp)

