#include <stdlib.h>
#include <table.h>

#include "test.h"

#include "unit/table_column.test"
#include "unit/table_row.test"
#include "unit/table_callback.test"
#include "unit/table_validator.test"
#include "unit/table_serialize.test"
#include "unit/table_sort.test"
#include "unit/table_binary_search.test"

static test tests[] = {
   { true, "column", table_column_test, {0} },
   { true, "row", table_row_test, {0} },
   { true, "callback", table_callback_test, {0} },
   { true, "validator", table_validator_test, {0} },
   { true, "serialize", table_serialize_test, {0} },
   { true, "sort", table_sort_test, {0} },
   { true, "binary search", table_binary_search_test, {0} },
   { false, NULL, NULL, {0} }
};

int main(int argc, char **argv)
{
   test *t;

   test_header("Table Unit Tests");
   for (t = tests; t->name; ++t)
      test_run(t);

   for (t = tests; t->name; ++t)
      if (!t->return_code)
	 return EXIT_FAILURE;
   
   return EXIT_SUCCESS;
}
