cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  da4cpp
  VERSION 0.1
  LANGUAGES C CXX
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. \
      Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

include(cmake/ProjectOptions.cmake)
include(cmake/Dependencies.cmake)
include(cmake/Documentation.cmake)

include(CTest)

enable_testing()

add_library(target_default_options INTERFACE)
target_include_directories(target_default_options INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(target_default_options INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_default_cxx_flags(target_default_options INTERFACE
  WARNINGS_AS_ERRORS ${WARNINGS_AS_ERRORS}
  CODE_COVERAGE ${CODE_COVERAGE}
)
enable_clang_tidy(target_default_options)

add_subdirectory(src)

option(DA4CPP_BUILD_TESTS "Build the testing tree" ON)
option(DA4CPP_BUILD_APPS "Build the applications" ON)
if(DA4CPP_BUILD_TESTS)
  add_subdirectory(tests)
endif()
if(DA4CPP_BUILD_APPS)
  add_subdirectory(apps)
endif()

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular header paths
# string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION) something packageProject( NAME ${PROJECT_NAME}
# VERSION ${PROJECT_VERSION} NAMESPACE ${PROJECT_NAME} BINARY_DIR ${PROJECT_BINARY_DIR} INCLUDE_DIR
# ${PROJECT_SOURCE_DIR}/include INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION} VERSION_HEADER
# "${VERSION_HEADER_LOCATION}" COMPATIBILITY SameMajorVersion DEPENDENCIES "clang" "llvm" )
