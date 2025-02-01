cmake_minimum_required(VERSION 3.14)
project(CpmAddTest LANGUAGES CXX)

enable_testing()

find_package(MyLibrary REQUIRED)

add_executable(cpm integration.cpp)
target_link_libraries(cpm PRIVATE MyLibrary)

# Register with CTest
add_test(NAME IntegrationTest COMMAND integration_test)

