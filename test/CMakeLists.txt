include_directories(${TABLE_INCLUDE_DIRS})
link_directories(${LIBRARY_OUTPUT_PATH})
add_executable(table_test table_test.c)
target_link_libraries(table_test table)