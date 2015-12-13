# libtable

[![FreeBSD License](https://img.shields.io/:license-freebsd-red.svg)](https://github.com/sgerbino/libtable/blob/master/COPYING)
[![Build Status](https://travis-ci.org/sgerbino/libtable.svg)](https://travis-ci.org/sgerbino/libtable)
[![Coverity Status](https://scan.coverity.com/projects/7249/badge.svg)](https://scan.coverity.com/projects/sgerbino-libtable)

## Introduction

The table library is a C implementation of a relational table with useful
features such as sorting, searching, and callback mechanisms. This document
describes the high level design of the table library and examples of its
usage.

If you are looking for the API documentation for libtable, please download
the source and generate the Doxygen documents.

```bash
cmake
make doc
```

## Example

```c
#include <stdio.h>
#include <table.h>

int main(int argc, char **argv)
{
   int id_col, value_col, row, col, num_rows, num_cols;
   
   table *t = table_new();
   
   id_col = table_add_column(t, "id", TABLE_INT);
   value_col = table_add_column(t, "value", TABLE_STRING);

   row = table_add_row(t);
   table_set_int(t, row, id_col, 1);
   table_set_string(t, row, value_col, "one");

   row = table_add_row(t);
   table_set_int(t, row, id_col, 2);
   table_set_string(t, row, value_col, "two");

   row = table_add_row(t);
   table_set_int(t, row, id_col, 3);
   table_set_string(t, row, value_col, "three");

   num_rows = table_get_row_length(t);
   num_cols = table_get_column_length(t);

   for (row = 0; row < num_rows; row++)
   {
      for (col = 0; col < num_cols; col++)
      {
         char buf[255];
         table_cell_to_buffer(t, row, col, buf, sizeof(buf));
         printf("%s\t", buf);
      }
      printf("\n");
   }

   table_delete(t);

   return 0;
}

```

Resulting output:
```bash
1	one	
2	two	
3	three	
```
