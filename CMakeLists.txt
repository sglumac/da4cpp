cmake_minimum_required(VERSION 3.19)
project(
  da4cpp
  VERSION 0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Werror")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")


if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. \
      Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME PackageProject.cmake
    GITHUB_REPOSITORY TheLartians/PackageProject.cmake
    GIT_TAG v1.8.0
)

CPMAddPackage(
    NAME m.css
    GITHUB_REPOSITORY mosra/m.css
    GIT_TAG a0d292ec311b97fefd21e93cdefb60f88d19ede6
)

find_package(Catch2 3 REQUIRED)

include(CTest)
include(Catch)

enable_testing()

add_subdirectory(da4cpp)
add_subdirectory(documentation)


# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION) something
# packageProject( NAME ${PROJECT_NAME} VERSION ${PROJECT_VERSION} NAMESPACE ${PROJECT_NAME}
# BINARY_DIR ${PROJECT_BINARY_DIR} INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include INCLUDE_DESTINATION
# include/${PROJECT_NAME}-${PROJECT_VERSION} VERSION_HEADER "${VERSION_HEADER_LOCATION}"
# COMPATIBILITY SameMajorVersion DEPENDENCIES "clang" "llvm" )
