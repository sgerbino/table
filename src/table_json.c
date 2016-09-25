#include <table.h>
#include <json.h>
#include <string.h>

static const char TABLE_COLUMN_NAME_KEY[] = "name";
static const char TABLE_COLUMN_DATA_TYPE_KEY[] = "data_type";
static const char TABLE_COLUMNS_KEY[] = "columns";
static const char TABLE_ROWS_KEY[] = "rows";

table* table_from_json_string(const char *json)
{
	json_object *object = json_tokener_parse(json);
	return table_from_json_object(object);
}

table* table_from_json_object(json_object *object)
{
	table *t = table_new();
	json_object_object_foreach(object, key, val)
	{
		if (!strcmp((const char*)key, TABLE_COLUMNS_KEY))
		{
			int columns_length = json_object_array_length(val);
			for (int i = 0; i < columns_length; i++)
			{
				const char *name = NULL;
				table_data_type data_type = 0;
				json_object *value = json_object_array_get_idx(val, i);
				json_object_object_foreach(value, inner_key, inner_value)
				{
					if (!strcmp((const char*)inner_key, TABLE_COLUMN_NAME_KEY))
						name = json_object_get_string(inner_value);
					else if (!strcmp((const char*)inner_key, TABLE_COLUMN_DATA_TYPE_KEY))
						data_type = json_object_get_int(inner_value);
				}
				table_add_column(t, name, data_type);
			}
		}

		if (!strcmp((const char*)key, TABLE_ROWS_KEY))
		{
			int rows_length = json_object_array_length(val);
			for (int row = 0; row < rows_length; row++)
			{
				json_object *columns = json_object_array_get_idx(val, row);
				int columns_length = json_object_array_length(columns);

				table_add_row(t);
				for (int column = 0; column < columns_length; column++)
				{
					json_object *cell_value = json_object_array_get_idx(columns, column);
					const char *buffer = json_object_get_string(cell_value);
					table_cell_from_buffer(t, row, column, buffer);
				}
			}
		}
	}
	return t;
}

json_object* table_to_json_object(table *t)
{
	json_object *object, *columns, *rows;
	int col_length, row_length;
	object = json_object_new_object();

	/* Add columns to the object */
	columns = json_object_new_array();
	
	col_length = table_get_column_length(t);
	for (int col_idx = 0; col_idx < col_length; col_idx++)
	{
		table_data_type type = table_get_column_data_type(t, col_idx);
		const char *name = table_get_column_name(t, col_idx);
		json_object *column = json_object_new_object();
		json_object_object_add(column, TABLE_COLUMN_NAME_KEY, json_object_new_string(name));
		json_object_object_add(column, TABLE_COLUMN_DATA_TYPE_KEY, json_object_new_int(type));
		json_object_array_add(columns, column);
	}

	json_object_object_add(object, TABLE_COLUMNS_KEY, columns);

	/* Add rows to the object */
	rows = json_object_new_array();
	
	row_length = table_get_row_length(t);
	for (int row_idx = 0; row_idx < row_length; row_idx++)
	{
		json_object *row = json_object_new_array();
		for (int col_idx = 0; col_idx < col_length; col_idx++)
		{
         if (!table_cell_has_value(t, row_idx, col_idx))
				continue;
            
			char buffer[512] = {0};
			table_cell_to_buffer(t, row_idx, col_idx, buffer, sizeof(buffer));
			json_object_array_add(row, json_object_new_string(buffer));
		}
		json_object_array_add(rows, row);
	}

	json_object_object_add(object, TABLE_ROWS_KEY, rows);

	return object;
}

const char* table_to_json_string(table *t)
{
	json_object *json = table_to_json_object(t);
	const char *json_string = json_object_to_json_string_ext(json, JSON_C_TO_STRING_PLAIN);
	//json_object_put(json);
	return json_string;
}
