#include <table.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void callback(table *t, int row, int col, table_event_type event_type, void *data)
{
   *(table_bitfield*)data |= event_type;
}

int main(int argc, char **argv)
{
	const int NUM_DATA_TYPES = 24;
	const int NUM_ROWS = 500;
	table_bitfield result = 0;
	time_t now;
	int column_index, row, num_cols;
	table *t = table_new();

	srand((unsigned int)time(&now));

	table_register_callback(t, callback, &result, ~0);
	
	for (column_index = 0; column_index < NUM_DATA_TYPES; column_index++) {
		char name[2] = {0};
		name[0] = (char)column_index;
		table_add_column(t, name, column_index);
	}

	num_cols = table_get_column_length(t);
	for (row = 0; row < NUM_ROWS; row++) {
		size_t pos;
		size_t data_size = 64;
		int col;
		char *data = malloc(data_size);

		/* Random number and valid string */
		for (pos = 0; pos < data_size - 1; pos++)
			data[pos] = rand() % 128;
		data[data_size - 1] = '\0';
		
		table_add_row(t);
		for (col = 0; col < num_cols; col++) {
			table_set(t, row, col, (void*)data, table_get_column_data_type(t, col));
		}
		
		free(data);
	}

	table_delete(t);

	return 0;
}
