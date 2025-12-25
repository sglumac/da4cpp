find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(Doxygen REQUIRED)

include(cmake/CPM.cmake)
CPMUsePackageLock(cmake/cpm-package-lock.cmake)

find_package(Catch2 REQUIRED)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

#CPMAddPackage(
#  NAME PackageProject.cmake
#  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
#  GIT_TAG v1.8.0
#)

