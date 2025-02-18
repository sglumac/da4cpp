add_subdirectory(da4cpp)

add_library(da4cpp lib.cpp)
target_link_libraries(da4cpp graph parsing default_project_cxx_flags)
target_include_directories(da4cpp PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(da4cpp_app main.cpp)
target_link_libraries(da4cpp_app da4cpp default_project_cxx_flags)
