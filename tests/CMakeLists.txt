cmake_minimum_required(VERSION 3.20)

include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)
FetchContent_MakeAvailable(doctest)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)

# da4cpp/parsing.tests
add_executable(parsing_tests parsing.tests.cpp)
target_compile_definitions(parsing_tests PRIVATE TEST_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(parsing_tests PRIVATE doctest::doctest da4cpp::parsing target_default_options)
configure_file(parsing.tests.resources/function_call.cpp parsing.tests.resources/function_call.cpp)
configure_file(
  parsing.tests.resources/struct_reference.cpp parsing.tests.resources/struct_reference.cpp
)
configure_file(
  parsing.tests.resources/struct_forward_declaration.cpp
  parsing.tests.resources/struct_forward_declaration.cpp
)
doctest_discover_tests(parsing_tests)

