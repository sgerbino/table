#include <table.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
   table t;
   int num_cols, id_col, name_col;
   int rc = 0;

   table_init(&t);
   
   id_col = table_add_column(&t, "id", TABLE_INT);
   name_col = table_add_column(&t, "name", TABLE_STRING);

   num_cols = table_get_column_length(&t);

   if (num_cols != 2)
   {
      printf("Failed to retrieve number of columns");
      rc = -1;
   }

   if (strcmp(table_get_column_name(&t, id_col), "id"))
   {
      printf("Failed to retrieve column name");
      rc = -1;
   }

   if (strcmp(table_get_column_name(&t, name_col), "name"))
   {
      printf("Failed to retrieve column name");
      rc = -1;
   }

   table_destroy(&t);

   return rc;
}
