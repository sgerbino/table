include_directories(${TABLE_INCLUDE_DIRS})
link_directories(${LIBRARY_OUTPUT_PATH})
add_executable(test_driver test_driver.c test.c)
target_link_libraries(test_driver table)