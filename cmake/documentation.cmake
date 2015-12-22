find_package(Doxygen)
if(DOXYGEN_FOUND)
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/doc)
  configure_file(${TABLE_CONF_DIR}/doxyfile.in ${CMAKE_BINARY_DIR}/doc/doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doc/doxyfile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)
