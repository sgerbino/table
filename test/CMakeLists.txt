include_directories(${TABLE_INCLUDE_DIR})
link_directories(${LIBRARY_OUTPUT_PATH})

set(TABLE_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/unit/table_test.h ${CMAKE_CURRENT_SOURCE_DIR}/test.h)

set(TABLE_TEST_SOURCES 
${CMAKE_CURRENT_SOURCE_DIR}/test.c
${CMAKE_CURRENT_SOURCE_DIR}/test_driver.c
${CMAKE_CURRENT_SOURCE_DIR}/unit/table_column_test.c
${CMAKE_CURRENT_SOURCE_DIR}/unit/table_row_test.c
${CMAKE_CURRENT_SOURCE_DIR}/unit/table_callback_test.c
${CMAKE_CURRENT_SOURCE_DIR}/unit/table_validator_test.c
${CMAKE_CURRENT_SOURCE_DIR}/unit/table_serialize_test.c
${CMAKE_CURRENT_SOURCE_DIR}/unit/table_sort_test.c
${CMAKE_CURRENT_SOURCE_DIR}/unit/table_binary_search_test.c)

add_executable(test_driver ${TABLE_TEST_SOURCES} ${TABLE_TEST_HEADERS})
target_link_libraries(test_driver table)
