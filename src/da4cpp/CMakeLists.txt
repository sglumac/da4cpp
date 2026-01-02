#################
# da4cpp::graph #
#################
add_library(graph graph.cpp)
target_include_directories(graph PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(graph PRIVATE target_default_options)
add_library(da4cpp::graph ALIAS graph)

###################
# da4cpp::parsing #
###################
add_library(parsing parsing.cpp)
target_include_directories(parsing PRIVATE ${LLVM_INCLUDE_DIRS})
target_include_directories(parsing PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(parsing PRIVATE ${LLVM_DEFINITIONS})
target_link_libraries(parsing PRIVATE libclang graph target_default_options)
add_library(da4cpp::parsing ALIAS parsing)

