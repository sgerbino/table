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

static test tests[] = {
   { true, "column", column_test, {0} },
   { true, "row", row_test, {0} },
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

   if (num_rows == random_number)
   {
      snprintf(buf, len, "Failed to retrieve row length, expected %d but received %d", random_number, num_rows);
      rc = false;
   }

   table_destroy(&t);

   return rc;
}
