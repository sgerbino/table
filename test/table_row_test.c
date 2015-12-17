#include <table.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
   table t;
   time_t now;
   int i, num_rows, random_number;
   int rc = 0;
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
      printf("Failed to retrieve row length, expected %d but received %d", random_number, num_rows);
      rc = -1;
   }

   table_destroy(&t);

   return rc;
}
