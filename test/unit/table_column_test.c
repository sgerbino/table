#include "table_test.h"

bool table_column_test(char *buf, size_t len)
{
   table t;
   int num_cols, id_col, name_col;
   bool rc = true;

   table_init(&t);
   
   id_col = table_add_column(&t, "id", TABLE_INT);
   name_col = table_add_column(&t, "name", TABLE_STRING);

   num_cols = table_get_column_length(&t);

   if (num_cols != 2)
   {
      snprintf(buf, len, "Failed to retrieve number of columns");
      rc = false;
   }

   if (strcmp(table_get_column_name(&t, id_col), "id"))
   {
      snprintf(buf, len, "Failed to retrieve column name");
      rc = false;
   }

   if (strcmp(table_get_column_name(&t, name_col), "name"))
   {
      snprintf(buf, len, "Failed to retrieve column name");
      rc = false;
   }

   table_destroy(&t);

   return rc;
}
