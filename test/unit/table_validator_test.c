#include "table_test.h"

bool table_validator_test(char *buf, size_t len)
{
   bool rc = true;
   int row;
   int col;
   table t;
   time_t now;

   srand(time(&now));
   row = rand();
   srand(time(&now));
   col = rand();

   table_init(&t);
   if (table_row_is_valid(&t, row))
   {
      snprintf(buf, len, "Row %d should not be valid", row);
      rc = false;
   }

   if (table_column_is_valid(&t, col))
   {
      snprintf(buf, len, "Column %d should not be valid", col);
      rc = false;
   }

   if (table_cell_is_valid(&t, row, col))
   {
      snprintf(buf, len, "Cell %d, %d should not be valid", row, col);
      rc = false;
   }

   row = table_add_row(&t);
   if (!table_row_is_valid(&t, row))
   {
      snprintf(buf, len, "Row %d should be valid", row);
      rc = false;
   }

   col = table_add_column(&t, "id", TABLE_INT);
   if (!table_column_is_valid(&t, col))
   {
      snprintf(buf, len, "Column %d should be valid", col);
      rc = false;
   }

   if (!table_cell_is_valid(&t, row, col))
   {
      snprintf(buf, len, "Cell %d, %d should be valid", row, col);
      rc = false;
   }
   table_destroy(&t);

   return rc;
}
