#ifndef TABLE_TEST_H_
#define TABLE_TEST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <table.h>

bool table_column_test(char *buf, size_t len);
bool table_row_test(char *buf, size_t len);
bool table_callback_test(char *buf, size_t len);
bool table_validator_test(char *buf, size_t len);
bool table_serialize_test(char *buf, size_t len);
bool table_sort_test(char *buf, size_t len);
bool table_binary_search_test(char *buf, size_t len);

#endif