#include "table_test.h"

bool table_binary_search_test(char *buf, size_t len)
{
   table t;
   int a_col, b_col;
   int a;
   float b;
   int row;
   int first, last;
   int inner_first, inner_last;
   bool rc = true;

   table_init(&t);

   a_col = table_add_column(&t, "a", TABLE_INT);
   b_col = table_add_column(&t, "b", TABLE_FLOAT);

   a = 0;
   b = 0.0f;
   for (row = 0; row < 100; row++)
   {
      if (row && !(row % 10))
      {
         ++a;
         b = 0.0f;
      }

      if (row && !(row % 2))
         b += 0.25;

      table_add_row(&t);
      table_set_int(&t, row, a_col, a);
      table_set_float(&t, row, b_col, b);
   }

   first = table_sorted_find_int(&t, a_col, 4, TABLE_FIRST);
   last = table_sorted_find_int(&t, a_col, 4, TABLE_LAST);

   if (first != 40)
   {
      snprintf(buf, len, "Expected first row to be 40 on column A, instead got %d", first);
      rc = false;
   }

   if (last != 49)
   {
      snprintf(buf, len, "Expected last row to be 49 on column A, instead got %d", last);
      rc = false;
   }

   inner_first = table_sorted_subset_find_float(&t, b_col, 0.5, TABLE_FIRST, first, last);
   inner_last = table_sorted_subset_find_float(&t, b_col, 0.5, TABLE_LAST, first, last);

   if (inner_first != 42)
   {
      snprintf(buf, len, "Expected inner first row to be 42 on column B, instead got %d", inner_first);
      rc = false;
   }

   if (inner_last != 43)
   {
      snprintf(buf, len, "Expected inner last row to be 43 on column B, instead got %d", inner_last);
      rc = false;
   }


#if 0 /* For debugging */
   {
      int num_rows, num_cols, col;
      num_rows = table_get_row_length(&t);
      num_cols = table_get_column_length(&t);
      for (row = 0; row < num_rows; ++row)
      {
         printf("row %d: ", row);
         for (col = 0; col < num_cols; ++col)
         {
            char buf[255];
            table_cell_to_string(&t, row, col, buf, sizeof buf);
            printf("%s\t", buf);
         }
         puts("\n");
      }
   }
#endif

   table_destroy(&t);

   return rc;
}
