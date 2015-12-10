#include <string.h>
#include "table_defs.h"

static void table_add_column_block(table *t);
static void table_remove_column_block(table *t);
static int table_column_add(table *t, const char *name, table_data_type data_type);
static int table_column_remove(table *t, int col_num);

/**
 * \brief Initialize a table column
 * \param[in] column_index The column column_index
 * \param[in] name The column name
 * \param[in] type The column data type
 * \param[in] func The column compare function
 */
void table_column_init(table *t, int column_index, const char *name, table_data_type type, table_compare_function func)
{
  table_column *column = table_get_col_ptr(t, column_index);
  column->name = malloc(strlen(name) + 1);
  if (column->name)
	  strcpy(column->name, name);
  column->type = type;
  column->compare = func;
}

/**
 * \brief Destroys a table column
 * \param[in] column The table column
 */
void table_column_destroy(table *t, int column)
{
  table_column *col = table_get_col_ptr(t, column);
  if (col->name)
    free(col->name);
}

/**
 * \brief Get the number of columns in the table
 * \param[in] table The table to examine
 * \return The number of columns
 */
int table_get_column_length(table *t)
{
  return t->column_length;
}

/**
 * \brief Get the column number from the column name
 * \param[in] table The table to retrieve the column number
 * \param[in] name The name of the column to target
 * \return The column number
 */
int table_get_column(table *t, const char *name)
{
  int column_index;
  int column_length = table_get_column_length(t);

  for (column_index = 0; column_index < column_length; column_index++)
    if (!strcmp(table_get_column_name(t, column_index), name))
      break;

  return column_index == column_length ? -1 : column_index;
}

/**
 * \brief Get the column type for a given column number
 * \param[in] t The table to be acted on
 * \param[in] column_index The table column
 * \return The columns table_data_type
 */
table_data_type table_get_column_data_type(table *t, int column_index)
{
  table_column *column = table_get_col_ptr(t, column_index);
  return column->type;
}

/**
 * \brief Add a new column to the table
 * \param[in] t The table to be acted on
 * \param[in] name The column name
 * \param[in] type The column data type
 * \return The column number
 */
int table_add_column(table *t, const char* name, table_data_type type)
{
  if (!(table_get_column_length(t) % t->column_block))
    table_add_column_block(t);

  table_column_add(t, name, type);
  table_notify(t, -1, table_get_column_length(t), TABLE_COLUMN_ADDED);
  return t->column_length++;
}

/**
 * \brief Delete a column from the table
 * \param[in] t The table to be acted on
 * \param[in] col The table column
 * \return A corresponding int
 */
int table_remove_column(table *t, int col)
{
  table_column_remove(t, col);
  t->column_length--;

  if (!(table_get_column_length(t) % t->column_block))
    table_remove_column_block(t);

  table_notify(t, -1, col, TABLE_COLUMN_REMOVED);
  return 0;
}

/**
 * \brief Get the name of a table column
 * \return The table column name
 */
const char* table_get_column_name(table *t, int col)
{
  table_column *col_ptr = table_get_col_ptr(t, col);
  return col_ptr->name;
}

/**
 * \brief Remove a block of columns
 * \param[out] table The table to be acted on
 */
static void table_remove_column_block(table *t)
{
  int num_rows, row;

  t->columns_allocated -= t->column_block;
  t->columns = realloc(t->columns, sizeof(table_column) * t->columns_allocated);

  num_rows = table_get_row_length(t);
  for (row = 0; row < num_rows; row++)
  {
    table_row *row_ptr = table_get_row_ptr(t, row);
    row_ptr->cells = realloc(row_ptr->cells, sizeof(table_cell) * t->columns_allocated);
  }
}

/**
 * \brief Add a block of columns
 * \param[out] table The table to be acted on
 */
static void table_add_column_block(table *t)
{
  int num_rows, row;

  t->columns_allocated += t->column_block;
  t->columns = realloc(t->columns, sizeof(table_column) * t->columns_allocated);

  num_rows = table_get_row_length(t);
  for (row = 0; row < num_rows; row++)
  {
    table_row *row_ptr = table_get_row_ptr(t, row);
    row_ptr->cells = realloc(row_ptr->cells, sizeof(table_cell) * t->columns_allocated);
  }

}

/**
 * \brief Sets the values of the next column
 * \param[out] t The table to be acted on
 * \param[in] name The column name
 * \param[in] type The table data type
 * \return A return code
 */
static int table_column_add(table *t, const char *name, table_data_type type)
{
  int row_length = table_get_row_length(t);
  int column_length = table_get_column_length(t);

  table_column_init(t, column_length, name, type, table_get_default_compare_function_for_data_type(type));

  for(int row = 0; row < row_length; row++)
    table_cell_init(t, row, column_length);

  return 0;
}

/**
 * \brief Removes a row from the table
 * \return The corresponding int
 */
static int table_column_remove(table *t, int column_index)
{
  table_column_destroy(t, column_index);

  int column_length = table_get_column_length(t);
  for(int i = column_index; i < (column_length - 1); i++)
  {
    memcpy(t->columns + i, t->columns + i + 1, sizeof(table_column));
  }

  /* Free extraneous cell values */
  int row_length = table_get_row_length(t);
  for(int i = 0; i < row_length; i++)
  {
    table_cell_destroy(t, i, column_index);

    /* Shift cells and overwrite deleted cell */
    table_row* row = table_get_row_ptr(t, i);
    for(int j = column_index; j < (column_length - 1); j++)
    {
      memcpy(row->cells + j, row->cells + j + 1, sizeof(table_cell));
    }
  }
  return 0;
}

/**
 * \brief Get the pointer of a particular column
 * \return The table column pointer
 */
table_column *table_get_col_ptr(table *t, int col)
{
  return t->columns + col;
}

/**
 * \brief Retrieve the column comparison function
 * \return The column comparison fucntion
 */
table_compare_function table_get_column_compare_function(table *t, int column)
{
  table_column *col_ptr = table_get_col_ptr(t, column);
  return col_ptr->compare;
}

/**
 * \brief Sets the columns compare function
 */
void table_set_column_compare_function(table *t, int column, table_compare_function function)
{
  table_column *col_ptr = table_get_col_ptr(t, column);
  col_ptr->compare = function;
}
