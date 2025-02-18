include("${CMAKE_CURRENT_LIST_DIR}/Warnings.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Coverage.cmake")

function(target_default_cxx_flags target scope WARNINGS_AS_ERRORS CODE_COVERAGE)
  set(oneValueArgs WARNINGS_AS_ERRORS CODE_COVERAGE)
  cmake_parse_arguments(PARSE_ARGV 0 ARG "" "${oneValueArgs}" "")
  target_default_project_cxx_warnings(${target} ${scope})

  if(NOT DEFINED ARG_WARNINGS_AS_ERRORS)
    set(ARG_WARNINGS_AS_ERRORS ON)
  endif()
  if (${ARG_WARNINGS_AS_ERRORS})
    target_warnings_as_errors(${target} ${scope})
  endif()

  if(NOT DEFINED ARG_CODE_COVERAGE)
    set(ARG_CODE_COVERAGE OFF)
  endif()
  if (${ARG_CODE_COVERAGE})
    target_code_coverage_options(${target} ${scope})
  endif()
endfunction()

