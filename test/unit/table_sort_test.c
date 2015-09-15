#include "table_test.h"

bool table_sort_test(char *buf, size_t len)
{
   table t;
   time_t now;
   int row, col, num_rows, num_cols, random_number, value_range = 20;
   bool rc = true;
   const size_t row_range = 100, col_range = 5;
   const size_t row_minimum = 100, col_minimum = 2;
   int error_row = -1;
   int error_column = -1;

   srand(time(&now));

   random_number = rand() % row_range + row_minimum;

   table_init(&t);

   for (row = 0; row < random_number; row++)
      table_add_row(&t);

   num_rows = table_get_row_length(&t);

   random_number = rand() % col_range + col_minimum;

   for (col = 0; col < random_number; col++)
   {
      char buf[255];
      snprintf(buf, sizeof(buf), "col-%d", col);
      table_add_column(&t, buf, TABLE_INT);
   }

   num_cols = table_get_column_length(&t);
   for (col = 0; col < num_cols; col++)
   {
      for (row = 0; row < num_rows; row++)
      {
         int value = rand() % value_range;
         table_set_int(&t, row, col, value);
      }
   }

   int *cols = calloc(num_cols, sizeof(int));
   table_order *sort_orders = calloc(num_cols, sizeof(table_order));
   for (col = 0; col < num_cols; col++)
   {
      cols[col] = col;
      sort_orders[col] = rand() % 2;
   }

   table_column_sort(&t, cols, sort_orders, num_cols);

   for (row = 0; row < num_rows; row++)
   {
      if (row > 0)
      {
         for (col = 0; col < num_cols; col++)
         {
            if (col > 0)
            {
               int prev_col;
               bool bail = false;
               for (prev_col = col - 1; prev_col >= 0; --prev_col)
               {
                  if (table_get_int(&t, row, prev_col) != table_get_int(&t, row - 1, prev_col))
                  {
                     bail = true;
                     break;
                  }
               }

               if (bail)
                  break;
            }

            if (sort_orders[col] == TABLE_ASCENDING)
            {
               if (table_get_int(&t, row - 1, col) > table_get_int(&t, row, col))
               {
                  snprintf(buf, len, "Row %d is not sorted correctly on column %d, sort order TABLE_ASCENDING", row, col);
                  error_row = row;
                  error_column = col;
                  rc = false;
               }
            }
            else
            {
               if (table_get_int(&t, row - 1, col) < table_get_int(&t, row, col))
               {
                  snprintf(buf, len, "Row %d is not sorted correctly on column %d, sort order TABLE_DESCENDING", row, col);
                  error_row = row;
                  error_column = col;
                  rc = false;
               }
            }
         }
      }
   }

   if (error_row != -1)
   {
      int context = 10;
      char buf[255];
      int row, col;
      int row_len = table_get_row_length(&t);
      int row_context_min = error_row - context >= 0 ? error_row - context : 0;
      int row_context_max = error_row + context <= row_len ? error_row + context : row_len;
      row_context_min = 0; row_context_max = table_get_row_length(&t);
      puts("\n");
      for (row = row_context_min; row < row_context_max; row++)
      {
         for (col = 0; col < table_get_column_length(&t); col++)
         {
            table_cell_to_buffer(&t, row, col, buf, sizeof buf);
            if (error_row == row && error_column == col)
               printf("%s*\t", buf);
            else
               printf("%s\t", buf);
         }
         if (error_row == row)
            puts("!\n");
         else
            puts("\n");
      }
   }


   table_destroy(&t);
   free(cols);
   free(sort_orders);

   return rc;
}
