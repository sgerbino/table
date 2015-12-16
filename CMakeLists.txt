cmake_minimum_required(VERSION 2.8)
project(TABLE C)

set(${PROJECT_NAME}_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# If cmake was called with this CMakeLists.txt as the top level, then we
# will set the up the build structure.
if (${CMAKE_CURRENT_SOURCE_DIR} MATCHES ${CMAKE_SOURCE_DIR})
  set(CMAKE_C_FLAGS "-Wall -std=c99")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/doc/${PROJECT_NAME_LOWER})
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${DOXYGEN_OUTPUT_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUTPUT_DIR}/Doxyfile
    WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)

add_custom_target(check
  test_driver
  WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
  COMMENT "Running Table unit tests"
)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
