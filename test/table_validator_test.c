#include <table.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
   int rc = 0;
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
      printf("Row %d should not be valid", row);
      rc = -1;
   }

   if (table_column_is_valid(&t, col))
   {
      printf("Column %d should not be valid", col);
      rc = -1;
   }

   if (table_cell_is_valid(&t, row, col))
   {
      printf("Cell %d, %d should not be valid", row, col);
      rc = -1;
   }

   row = table_add_row(&t);
   if (!table_row_is_valid(&t, row))
   {
      printf("Row %d should be valid", row);
      rc = -1;
   }

   col = table_add_column(&t, "id", TABLE_INT);
   if (!table_column_is_valid(&t, col))
   {
      printf("Column %d should be valid", col);
      rc = -1;
   }

   if (!table_cell_is_valid(&t, row, col))
   {
      printf("Cell %d, %d should be valid", row, col);
      rc = -1;
   }
   table_destroy(&t);

   return rc;
}
