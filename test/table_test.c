#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <table.h>

typedef struct _test {
   bool return_code;
   const char *name;
   bool (*function)(void);
} test;

bool column_test(void);
bool row_test(void);

test tests[] = {
   { true, "column", column_test },
   { true, "row", row_test },
   { NULL, NULL, NULL }
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
	 return -1;
   
   return 0;
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
   t->return_code = t->function();
   c = clock() - c;
   elapsed = (double)c/CLOCKS_PER_SEC*1000;
   printf(" %.3fms [ %4s ]\n", elapsed, t->return_code ? "PASS" : "FAIL");
}

bool column_test(void)
{
   table t;
   int num_cols, id_col, name_col;
   bool rc = true;

   table_init(&t);
   
   id_col = table_add_column(&t, "id", TABLE_INT);
   name_col = table_add_column(&t, "name", TABLE_STRING);

   num_cols = table_get_column_length(&t);

   if (num_cols != 2)
      rc = false;

   if (strcmp(table_get_column_name(&t, id_col), "id"))
      rc = false;

   if (strcmp(table_get_column_name(&t, name_col), "name"))
      rc = false;

   table_destroy(&t);

   return rc;
}

bool row_test(void)
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
      rc = false;

   table_destroy(&t);

   return rc;
}
