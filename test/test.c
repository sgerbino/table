#include "test.h"

void test_header(const char *title)
{
   size_t i;
   size_t len = strlen(title);
   printf("%s\n", title);
   for (i = 0; i < len; ++i) putchar('-');
   putchar('\n');
}

void test_run(test *t)
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
