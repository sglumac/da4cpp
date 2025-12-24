find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(Doxygen REQUIRED)

include(cmake/CPM.cmake)
CPMUsePackageLock(cmake/cpm-package-lock.cmake)

CPMAddPackage(
  NAME Catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 3.4.0
)
find_package(Catch2 REQUIRED)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

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

