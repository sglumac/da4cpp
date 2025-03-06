include(cmake/CPM.cmake)

find_package(Catch2 3 REQUIRED)

include(CTest)
include(Catch)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  GIT_TAG v1.8.0
)
CPMAddPackage(
    NAME CLI11
    GITHUB_REPOSITORY CLIUtils/CLI11
    GIT_TAG v2.5.0
)

