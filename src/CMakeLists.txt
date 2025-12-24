############
# da4cpp/* #
############
add_subdirectory(da4cpp)

##########
# da4cpp #
##########
add_library(da4cpp da4cpp.cpp)
target_link_libraries(da4cpp graph parsing target_default_options)
target_include_directories(da4cpp PUBLIC ${CMAKE_SOURCE_DIR}/src)

##############
# run_da4cpp #
##############
add_executable(run_da4cpp main.cpp)
target_link_libraries(run_da4cpp da4cpp CLI11::CLI11 target_default_options)

