#include <stdio.h>
#include <string.h>
#include <table.h>

typedef enum _return_code {
   PASS,
   FAIL
} return_code;

void result(const char *entry, return_code rc);

return_code add_columns(table *t);
return_code check_columns(table *t);

return_code add_rows(table *t);
return_code check_rows(table *t);

return_code add_data(table *t);
return_code check_data(table *t);

int main(int argc, char **argv)
{
   table *t = table_new();
   int i;

   printf("table test\n");
   for (i = 0; i < 34; i++) putchar('-');
   putchar('\n');

   result("column check", add_columns(t) | check_columns(t));
   result("row check", add_rows(t) | check_rows(t));
   result("data check", add_data(t) | check_data(t));

   table_delete(t);
   return 0;
}

void result(const char *entry, return_code rc)
{
   printf("%-25s [ %4s ]\n", entry, PASS == rc ? "PASS" : "FAIL");
}

return_code add_columns(table *t)
{
   table_add_column(t, "id", TABLE_INT);
   table_add_column(t, "name", TABLE_STRING);
   return 0;
}

return_code check_columns(table *t)
{
   return_code rc = PASS;
   int num_cols = table_get_column_length(t);

   if (num_cols != 2)
      rc = FAIL;

   if (strcmp(table_get_column_name(t, 0), "id"))
      rc = FAIL;

   if (strcmp(table_get_column_name(t, 1), "name"))
      rc = FAIL;

   return rc;
}

return_code add_rows(table *t)
{
   table_add_row(t);
   table_add_row(t);
   table_add_row(t);
   return PASS;
}

return_code check_rows(table *t)
{
   return_code rc = PASS;
   if (table_get_row_length(t) != 3)
      rc = FAIL;
   return rc;
}

return_code add_data(table *t)
{
   int num_rows = table_get_row_length(t);
   int row;

   for (row = 0; row < num_rows; row++)
   {
      char buf[255];
      snprintf(buf, 255, "name %d", row);
      table_set_int(t, row, 0, row);
      table_set_string(t, row, 1, buf);
   }

   return PASS;
}

return_code check_data(table *t)
{
   return_code rc = PASS;
   int num_rows = table_get_row_length(t);
   int row;

   for (row = 0; row < num_rows; row++)
   {
      char buf[255];
      snprintf(buf, 255, "name %d", row);

      if (table_get_int(t, row, 0) != row)
         rc = FAIL;

      if (strcmp(table_get_string(t, row, 1), buf))
         rc = FAIL;
   }
   return rc;
}
