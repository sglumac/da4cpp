cmake_minimum_required(VERSION 3.14)
project(IntegrationTests LANGUAGES CXX)

# Enable testing
enable_testing()

# Find the library
find_package(MyLibrary REQUIRED)

add_executable(cpm integration.cpp)
target_link_libraries(integration_test PRIVATE MyLibrary)

# Register with CTest
add_test(NAME IntegrationTest COMMAND integration_test)

