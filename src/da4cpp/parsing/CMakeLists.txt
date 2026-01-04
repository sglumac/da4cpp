#############################
# da4cpp::parsing::handlers #
#############################
add_library(da4cpp_parsing_handlers handlers.cpp filters.cpp processors.cpp)
target_link_libraries(da4cpp_parsing_handlers PRIVATE target_default_options)
target_include_directories(da4cpp_parsing_handlers PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(da4cpp_parsing_handlers PRIVATE ${LLVM_DEFINITIONS})
add_library(da4cpp::parsing::handlers ALIAS da4cpp_parsing_handlers)

