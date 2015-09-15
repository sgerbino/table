#include "table_test.h"

bool table_row_test(char *buf, size_t len)
{
   table t;
   time_t now;
   int i, num_rows, random_number;
   bool rc = true;
   const size_t range = 100;
   const size_t minimum = 100;

   srand(time(&now));
   
   random_number = rand() % range + minimum;

   table_init(&t);

   for (i = 0; i < random_number; ++i)
      table_add_row(&t);

   num_rows = table_get_row_length(&t);

   if (num_rows != random_number)
   {
      snprintf(buf, len, "Failed to retrieve row length, expected %d but received %d", random_number, num_rows);
      rc = false;
   }

   table_destroy(&t);

   return rc;
}
