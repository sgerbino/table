find_package(Git)
if(GIT_FOUND)
  add_custom_target(
    version
    ${CMAKE_COMMAND} -D SOURCE=${TABLE_CONF_DIR}/version.h.in
    -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
    -D DESTINATION=${CMAKE_BINARY_DIR}/include/version.h
    -D WORK_DIR=${CMAKE_CURRENT_SOURCE_DIR}
    -P ${TABLE_CMAKE_DIR}/version.cmake
    COMMENT "Retrieving semantic versioning information" VERBATIM
    )
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --dirty --always --tags
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE TABLE_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" TABLE_MAJOR_VERSION "${TABLE_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" TABLE_MINOR_VERSION "${TABLE_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" TABLE_PATCH_VERSION "${TABLE_VERSION}")
  configure_file(${TABLE_CONF_DIR}/version.h.in ${CMAKE_BINARY_DIR}/include/version.h)
else()
  add_custom_target(
    version
    COMMENT "No semantic versioning information available" VERBATIM
    )
  set(TABLE_MAJOR_VERSION 0)
  set(TABLE_MINOR_VERSION 0)
  set(TABLE_PATCH_VERSION 0)
  set(TABLE_VERSION "")
  configure_file(${TABLE_CONF_DIR}/version.h.in ${CMAKE_BINARY_DIR}/include/version.h)
endif(GIT_FOUND)
