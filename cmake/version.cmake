execute_process(
  COMMAND ${GIT_EXECUTABLE} describe --dirty --always --tags
  WORKING_DIRECTORY ${WORK_DIR}
  OUTPUT_VARIABLE TABLE_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
string(REGEX MATCH "^[0-9]+\\.[0-9]+\\.[0-9]+" TABLE_VALID_VERSION "${TABLE_VERSION}")
if (TABLE_VALID_VERSION)
  string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" TABLE_MAJOR_VERSION "${TABLE_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" TABLE_MINOR_VERSION "${TABLE_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" TABLE_PATCH_VERSION "${TABLE_VERSION}")
else()
  set(TABLE_MAJOR_VERSION 0)
  set(TABLE_MINOR_VERSION 0)
  set(TABLE_PATCH_VERSION 0)
  set(TABLE_VERSION "")
endif(TABLE_VALID_VERSION)
configure_file(${SOURCE} ${DESTINATION} @ONLY)
