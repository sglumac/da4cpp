include("${CMAKE_CURRENT_LIST_DIR}/ProjectWarnings.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/CoverageOptions.cmake")

function(target_default_cxx_flags target scope WARNINGS_AS_ERRORS CODE_COVERAGE)
  target_default_project_cxx_warnings(${target} ${scope})
  if (${WARNINGS_AS_ERRORS})
    target_warnings_as_errors(${target} ${scope})
  endif()
  if (${CODE_COVERAGE})
    target_code_coverage_options(${target} ${scope})
  endif()
endfunction()

