############
# da4cpp/* #
############
add_subdirectory(da4cpp)

##########
# da4cpp #
##########
add_library(da4cpp da4cpp.cpp)
target_link_libraries(da4cpp da4cpp::graph da4cpp::parsing target_default_options)
target_include_directories(da4cpp PUBLIC ${CMAKE_SOURCE_DIR}/src)
add_library(da4cpp::da4cpp ALIAS da4cpp)

