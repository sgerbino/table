# table

[![FreeBSD License](https://img.shields.io/:license-freebsd-red.svg)](https://github.com/sgerbino/table/blob/master/COPYING.txt)
[![Build Status](https://travis-ci.org/sgerbino/table.svg?branch=master)](https://travis-ci.org/sgerbino/table)
[![Build Status](https://ci.appveyor.com/api/projects/status/g719foxpitcnas2s/branch/master?svg=true)](https://ci.appveyor.com/project/sgerbino/table)
[![Coverity Status](https://scan.coverity.com/projects/7249/badge.svg)](https://scan.coverity.com/projects/sgerbino-table)

## Table of contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
	- [Basic example](#basic-example)
	- [Callback example](#callback-example)
- [License](#license)

## Introduction

The table library is a C implementation of a relational table with useful
features such as sorting, searching, and callback mechanisms. This document
describes the high level design of the table library and examples of its
usage.

If you are looking for the API documentation for table, please download
the source and generate the Doxygen documents.

```bash
cmake
make doc
```

## Installation

Currently the only method of obtaining table is by building the sources.
The project requires a C99 compliant compiler and has no dependencies other
than the C standard library. Continuous integration tests both clang and gcc.

```bash
git clone https://github.com/sgerbino/table.git
cd table
cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local
make install
```

## Usage


### Basic example

This snippet demonstrates instantiating a table object, adding a basic schema 
of a several of columns and rows, then populating their values. The table knows 
how to convert its values to a string, so we take advantage of the function 
table_cell_to_buffer().

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

The resulting output:
 
```bash
1	one	
2	two	
3	three	
```

### Callback example

This snippet demonstrates the callback functionality. Like the simple example,
we're creating several rows and column; only this time we've registered a
callback function to notify us of changes. We've also decided to use table as
a stack variable, so table_init() and table_destroy() are used instead of
table_new() and table_delete().

```c
#include <stdio.h>
#include <table.h>

static void callback(table *t, int row, int col, table_event_type event_type, void *data)
{
	char *event_name = "UNKNOWN";
	switch (event_type)
	{
	case TABLE_ROW_ADDED:
		event_name = "TABLE_ROW_ADDED";
		break;
	case TABLE_COLUMN_ADDED:
		event_name = "TABLE_COLUMN_ADDED";
		break;
	case TABLE_DATA_MODIFIED:
		event_name = "TABLE_DATA_MODIFIED";
		break;
	case TABLE_ROW_REMOVED:
		event_name = "TABLE_ROW_REMOVED";
		break;
	case TABLE_COLUMN_REMOVED:
		event_name = "TABLE_COLUMN_REMOVED";
		break;
	case TABLE_DESTROYED:
		event_name = "TABLE_DESTROYED";
		break;
	}
	printf("received %s notification (row: %d, col: %d)\n", event_name, row, col);
}

int main(int argc, char **argv)
{
	int int64_col, uint64_col, boundary_col, row, col, num_rows, num_cols;
	table t;

	table_init(&t);

	table_register_callback(&t, callback, NULL, ~0);

	int64_col = table_add_column(&t, "int64", TABLE_INT64);
	uint64_col = table_add_column(&t, "uint64", TABLE_UINT64);
	boundary_col = table_add_column(&t, "boundary", TABLE_STRING);

	row = table_add_row(&t);
	table_set_int64(&t, row, int64_col, INT64_MAX);
	table_set_uint64(&t, row, uint64_col, UINT64_MAX);
	table_set_string(&t, row, boundary_col, "MAX");

	row = table_add_row(&t);
	table_set_int64(&t, row, int64_col, INT64_MIN);
	table_set_uint64(&t, row, uint64_col, 0);
	table_set_string(&t, row, boundary_col, "MIN");

	num_rows = table_get_row_length(&t);
	num_cols = table_get_column_length(&t);

	for (col = 0; col < num_cols; col++)
		printf("%25s\t", table_get_column_name(&t, col));

	printf("\n");

	for (row = 0; row < num_rows; row++) {
		for (col = 0; col < num_cols; col++) {
			char buf[255];
			table_cell_to_buffer(&t, row, col, buf, sizeof(buf));
			printf("%25s\t", buf);
		}
		printf("\n");
	}

	for (row = table_get_row_length(&t) - 1; row >= 0; row--)
		table_remove_row(&t, row);

	for (col = table_get_column_length(&t) - 1; col >= 0; col--)
		table_remove_column(&t, col);

	table_destroy(&t);

	return 0;
}
```

The resulting output:

```bash
received TABLE_COLUMN_ADDED notification (row: -1, col: 0)
received TABLE_COLUMN_ADDED notification (row: -1, col: 1)
received TABLE_COLUMN_ADDED notification (row: -1, col: 2)
received TABLE_ROW_ADDED notification (row: 0, col: -1)
received TABLE_DATA_MODIFIED notification (row: 0, col: 0)
received TABLE_DATA_MODIFIED notification (row: 0, col: 1)
received TABLE_DATA_MODIFIED notification (row: 0, col: 2)
received TABLE_ROW_ADDED notification (row: 1, col: -1)
received TABLE_DATA_MODIFIED notification (row: 1, col: 0)
received TABLE_DATA_MODIFIED notification (row: 1, col: 1)
received TABLE_DATA_MODIFIED notification (row: 1, col: 2)
                    int64	                   uint64	                 boundary	
      9223372036854775807	     18446744073709551615	                      MAX	
     -9223372036854775808	                        0	                      MIN	
received TABLE_ROW_REMOVED notification (row: 1, col: -1)
received TABLE_ROW_REMOVED notification (row: 0, col: -1)
received TABLE_COLUMN_REMOVED notification (row: -1, col: 2)
received TABLE_COLUMN_REMOVED notification (row: -1, col: 1)
received TABLE_COLUMN_REMOVED notification (row: -1, col: 0)
received TABLE_DESTROYED notification (row: -1, col: -1)
```

## License

This project uses the "FreeBSD License" or "Simplified BSD License" making it
compatible with both commercial software licenses and the GNU/GPL. For more
information see [COPYING.txt](https://github.com/sgerbino/table/blob/master/COPYING.txt).
