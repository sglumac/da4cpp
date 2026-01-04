####################
# da4cpp/parsing/* #
####################
add_subdirectory(parsing)

#################
# da4cpp::graph #
#################
add_library(da4cpp_graph graph.cpp)
target_link_libraries(da4cpp_graph PRIVATE target_default_options)
add_library(da4cpp::graph ALIAS da4cpp_graph)

###################
# da4cpp::parsing #
###################
add_library(da4cpp_parsing parsing.cpp)
target_include_directories(da4cpp_parsing PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(da4cpp_parsing PRIVATE ${LLVM_DEFINITIONS})
target_link_libraries(da4cpp_parsing PRIVATE libclang da4cpp::graph da4cpp::parsing::handlers target_default_options)
add_library(da4cpp::parsing ALIAS da4cpp_parsing)

