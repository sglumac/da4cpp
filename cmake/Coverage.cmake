function(target_code_coverage_options target scope)
  target_compile_options(${target} ${scope}
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
      --coverage -O0 -g
    >
  )
  target_link_options(${target} ${scope}
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
      --coverage
    >
  )
endfunction()
