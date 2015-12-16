#include <unistd.h>
#include <stdio.h>
#include "test.h"

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

static const char *test_pass_string()
{
	if (isatty(STDOUT_FILENO))
		return GRN"PASS"NRM;
	return "PASS";
}

static const char *test_fail_string()
{
	if (isatty(STDOUT_FILENO))
		return RED"FAIL"NRM;
	return "FAIL";
}

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
   printf(" %.3fms [ %4s ]\n", elapsed, return_code ? test_pass_string() : test_fail_string());
   
   if (strlen(t->buf) > 0)
      printf(" `-> %s\n", t->buf);
   
   return return_code;
}
