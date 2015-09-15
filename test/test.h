#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct _test {
   int id;
   const char *name;
   bool (*function)(char*, size_t);
   char buf[1024];
} test;


bool test_run(test *t);
void test_header(const char *title);
