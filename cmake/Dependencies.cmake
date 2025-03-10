find_package(Catch2 3 REQUIRED)
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(Doxygen REQUIRED)

include(CTest)
include(Catch)

include(cmake/CPM.cmake)
CPMUsePackageLock(cmake/cpm-package-lock.cmake)

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

