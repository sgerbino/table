link_directories(${LIBRARY_OUTPUT_PATH})

add_executable(table_column_test table_column_test.c)
target_link_libraries(table_column_test table)
add_test(NAME table-column-test
  COMMAND table_column_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(table_row_test ${CMAKE_CURRENT_SOURCE_DIR}/table_row_test.c)
target_link_libraries(table_row_test table)
add_test(NAME table-row-test
  COMMAND table_row_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(table_callback_test ${CMAKE_CURRENT_SOURCE_DIR}/table_callback_test.c)
target_link_libraries(table_callback_test table)
add_test(NAME table-callback-test
  COMMAND table_callback_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(table_validator_test ${CMAKE_CURRENT_SOURCE_DIR}/table_validator_test.c)
target_link_libraries(table_validator_test table)
add_test(NAME table-validator-test
  COMMAND table_validator_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(table_sort_test ${CMAKE_CURRENT_SOURCE_DIR}/table_sort_test.c)
target_link_libraries(table_sort_test table)
add_test(NAME table-sort-test
  COMMAND table_sort_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(table_binary_search_test ${CMAKE_CURRENT_SOURCE_DIR}/table_binary_search_test.c)
target_link_libraries(table_binary_search_test table)
add_test(NAME table-binary-search-test
  COMMAND table_binary_search_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(table_version_test ${CMAKE_CURRENT_SOURCE_DIR}/table_version_test.c)
target_link_libraries(table_version_test table)
add_test(NAME table-version-test
  COMMAND table_version_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(table_memtest ${CMAKE_CURRENT_SOURCE_DIR}/table_memtest.c)
target_link_libraries(table_memtest table)
add_test(NAME table-memtest
  COMMAND table_memtest
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(table_json_test ${CMAKE_CURRENT_SOURCE_DIR}/table_json_test.c)
target_link_libraries(table_json_test table)
add_test(NAME table-json-test
  COMMAND table_json_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
