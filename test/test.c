#include "test.h"

/**
 * \brief Prints the test title to standard out
 * \param[in] title The title to be printed
 */
void test_header(const char *title)
{
   size_t i;
   size_t len = strlen(title);
   printf("%s\n", title);
   for (i = 0; i < len; ++i) putchar('-');
   putchar('\n');
}

/**
 * \brief Run the test
 * \param[in,out] t The test
 * \return true if the test has passed, otherwise false
 */
bool test_run(test *t)
{
   bool return_code;
   clock_t c;
   double elapsed;
   char buf[64];
   
   c = clock();
   snprintf(buf, sizeof buf, "Running %s test (test id %d)...", t->name, t->id);
   printf("%-60s", buf);
   return_code = t->function(t->buf, sizeof t->buf);
   c = clock() - c;
   elapsed = (double)c/CLOCKS_PER_SEC*1000;
   printf(" %.3fms [ %4s ]\n", elapsed, return_code ? "PASS" : "FAIL");
   
   if (strlen(t->buf) > 0)
      printf(" `-> %s\n", t->buf);
   
   return return_code;
}
