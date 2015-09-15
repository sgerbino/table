#include <table.h>

#include "test.h"
#include "unit/table_test.h"

typedef enum _test_id
{
  TABLE_COLUMN_TEST,
  TABLE_ROW_TEST,
  TABLE_CALLBACK_TEST,
  TABLE_VALIDATOR_TEST,
  TABLE_SERIALIZE_TEST,
  TABLE_SORT_TEST,
  TABLE_BINARY_SEARCH_TEST,
  TABLE_END_TEST
} test_id;

static test tests[] = {
   { TABLE_COLUMN_TEST, "column", table_column_test },
   { TABLE_ROW_TEST, "row", table_row_test },
   { TABLE_CALLBACK_TEST, "callback", table_callback_test },
   { TABLE_VALIDATOR_TEST, "validator", table_validator_test },
   { TABLE_SERIALIZE_TEST, "serialize", table_serialize_test },
   { TABLE_SORT_TEST, "sort", table_sort_test },
   { TABLE_BINARY_SEARCH_TEST, "binary search", table_binary_search_test }
};

int main(int argc, char **argv)
{
   int id;
   int return_code = EXIT_SUCCESS;

   for (id = 0, test_header("Table Unit Tests"); id < TABLE_END_TEST; id++)
     return_code = test_run(&tests[id]) ? return_code : EXIT_FAILURE;
   
   return return_code;
}
