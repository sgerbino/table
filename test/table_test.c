#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <table.h>

typedef struct _test {
   bool return_code;
   const char *name;
   bool (*function)(char*, size_t);
   char buf[1024];
} test;

bool column_test(char *buf, size_t len);
bool row_test(char *buf, size_t len);
bool callback_test(char *buf, size_t len);
bool validator_test(char *buf, size_t len);

static test tests[] = {
   { true, "column", column_test, {0} },
   { true, "row", row_test, {0} },
   { true, "callback", callback_test, {0} },
   { true, "validator", validator_test, {0} },
   { false, NULL, NULL, {0} }
};

void run_test(test *t);
void print_header(const char *title);

int main(int argc, char **argv)
{
   const char *title = "Table Unit Tests";
   test *t;

   print_header(title);
   for (t = tests; t->name; ++t)
      run_test(t);

   for (t = tests; t->name; ++t)
      if (!t->return_code)
	 return EXIT_FAILURE;
   
   return EXIT_SUCCESS;
}

void print_header(const char *title)
{
   size_t i;
   size_t len = strlen(title);
   printf("%s\n", title);
   for (i = 0; i < len; ++i) putchar('-');
   putchar('\n');
}

void run_test(test *t)
{
   clock_t c;
   double elapsed;
   char buf[64];
   c = clock();
   snprintf(buf, sizeof buf, "Running %s test...", t->name);
   printf("%-40s", buf);
   t->return_code = t->function(t->buf, sizeof t->buf);
   c = clock() - c;
   elapsed = (double)c/CLOCKS_PER_SEC*1000;
   printf(" %.3fms [ %4s ]\n", elapsed, t->return_code ? "PASS" : "FAIL");
   if (strlen(t->buf) > 0)
      printf(" `-> %s\n", t->buf);
}

bool column_test(char *buf, size_t len)
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

bool row_test(char *buf, size_t len)
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

static void table_callback(table *t, int row, int col, table_event_type event_type, void *data)
{
   *(table_bitfield*)data |= event_type;
}

bool callback_test(char *buf, size_t len)
{
   table t;
   table_bitfield result = 0;
   bool rc = true;
   int row;
   int col;
   
   table_init(&t);
   table_register_callback(&t, table_callback, &result, ~0);
   
   row = table_add_row(&t);
   if (!(result & TABLE_ROW_ADDED))
   {
      snprintf(buf, len, "Failed to receive TABLE_ROW_ADDED event");
      rc = false;
   }

   col = table_add_column(&t, "id", TABLE_INT);
   if (!(result & TABLE_COLUMN_ADDED))
   {
      snprintf(buf, len, "Failed to receive TABLE_COLUMN_ADDED event");
      rc = false;
   }

   table_set_int(&t, row, col, 42);
   if (!(result & TABLE_DATA_MODIFIED))
   {
      snprintf(buf, len, "Failed to receive TABLE_DATA_MODIFIED event");
      rc = false;
   }

   table_remove_row(&t, row);
   if (!(result & TABLE_ROW_REMOVED))
   {
      snprintf(buf, len, "Failed to receive TABLE_ROW_REMOVED event");
      rc = false;
   }

   table_remove_column(&t, col);
   if (!(result & TABLE_COLUMN_REMOVED))
   {
      snprintf(buf, len, "Failed to receive TABLE_COLUMN_REMOVED event");
      rc = false;
   }

   table_unregister_callback(&t, table_callback, &result);
   table_destroy(&t);
   return rc;
}

bool validator_test(char *buf, size_t len)
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
