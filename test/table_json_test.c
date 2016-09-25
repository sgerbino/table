#include <table.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
   table *t1 = table_new();
	int int_col = table_add_column(t1, "integer", TABLE_INT);
	int string_col = table_add_column(t1, "string", TABLE_STRING);
	int double_col = table_add_column(t1, "float", TABLE_DOUBLE);
    
	int row = table_add_row(t1);
	table_set_int(t1, row, int_col, 10);
	table_set_string(t1, row, string_col, "ten");
   table_set_double(t1, row, double_col, 10.00000025);
	
	row = table_add_row(t1);
	table_set_int(t1, row, int_col, 20);
	table_set_string(t1, row, string_col, "twenty");
	table_set_double(t1, row, double_col, 20.000000025);
    
	row = table_add_row(t1);
	table_set_int(t1, row, int_col, 30);
	table_set_string(t1, row, string_col, "thirty");
	table_set_double(t1, row, double_col, 30.0000000025);
    
   const char *json = table_to_json_string(t1);

	printf("Table 1 JSON:\n%s\n", json);
	printf("\nParsed table 1:\n");
	printf("\tColumn length: %d\n", table_get_column_length(t1));
	printf("\tRow length: %d\n", table_get_row_length(t1));
	
	table *t2 = table_from_json_string(json);
	json = table_to_json_string(t2);
	printf("Table 2 JSON:\n%s\n", json);
	printf("\nParsed table 2:\n");
	printf("\tColumn length: %d\n", table_get_column_length(t2));
	printf("\tRow length: %d\n", table_get_row_length(t2));
	
	table_destroy(t1);
   table_destroy(t2);

   return 0;
}
