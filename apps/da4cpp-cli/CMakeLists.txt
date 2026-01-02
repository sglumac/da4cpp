add_executable(da4cpp-cli main.cpp)

target_link_libraries(da4cpp-cli PRIVATE da4cpp::da4cpp)

install(TARGETS da4cpp-cli
    RUNTIME DESTINATION bin
    COMPONENT cli
)

