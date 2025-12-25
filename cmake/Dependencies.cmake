find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(Doxygen REQUIRED)

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)
FetchContent_MakeAvailable(doctest)
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)

#CPMAddPackage(
#  NAME PackageProject.cmake
#  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
#  GIT_TAG v1.8.0
#)

