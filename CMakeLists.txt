cmake_minimum_required(VERSION 2.8)
project(TABLE)

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

# If cmake was called with this CMakeLists.txt as the top level, then we
# will set the up the build structure.
if (${CMAKE_CURRENT_SOURCE_DIR} MATCHES ${CMAKE_SOURCE_DIR})
  set(CMAKE_C_FLAGS "-Wall -std=c99")
  set(CMAKE_CXX_FLAGS "-Wall")
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin CACHE PATH "Executable directory" FORCE)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib CACHE PATH "Library directory" FORCE)
endif()

# Add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/doc/${PROJECT_NAME_LOWER})
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${DOXYGEN_OUTPUT_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUTPUT_DIR}/Doxyfile
    WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
