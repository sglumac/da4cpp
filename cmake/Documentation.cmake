add_custom_target(docs ALL
  COMMENT "Generating documentation with Doxygen and Sphinx"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/build/docs/doxygen"
  COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/Doxyfile"
  COMMAND "${SPHINX_EXECUTABLE}" -b html -W -n
          "${CMAKE_SOURCE_DIR}/docs"         # Source directory with conf.py
          "${CMAKE_SOURCE_DIR}/build/docs/sphinx"  # Output directory for Sphinx
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"  # Root is safe, but can also use docs/
  USES_TERMINAL
)

