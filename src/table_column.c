#include "table_private.h"

/**
 * \brief Get the number of columns in the table
 * \param[in] table The table to examine
 * \return The number of columns
 */
int table_get_column_length(table *t)
{
  return t->cols_len;
}

/**
 * \brief Get the column number from the column name
 * \param[in] table The table to retrieve the column number
 * \param[in] name The name of the column to target
 * \return The column number
 */
int table_get_column(table *t, const char *name)
{
  int col_num, num_cols, i;
  num_cols = table_get_column_length(t);
  col_num = -1;
  for(i = 0; i < num_cols; i++)
  {
    table_column *col;
    col = table_get_col_ptr(t, i);
    if(!strcmp(col->name, name))
    {
      col_num = i;
      break;
    }
  }
  return col_num;
}

/**
 * \brief Get the column type for a given column number
 * \param[in] t The table to be acted on
 * \param[in] col The table column
 * \return The columns table_data_type
 */
table_data_type table_get_column_data_type(table *t, int col)
{
  table_column *col_ptr = table_get_col_ptr(t, col);
  table_data_type retval = col_ptr->type;
  return retval;
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
  if(!(table_get_column_length(t) % t->col_block))
  {
    table_add_column_block(t);
  }

  table_col_add(t, name, type);
  table_notify(t, -1, t->cols_len, TABLE_COLUMN_ADDED);

  return t->cols_len++;
}

/**
 * \brief Delete a column from the table
 * \param[in] t The table to be acted on
 * \param[in] col The table column
 * \return A corresponding int
 */
int table_remove_column(table *t, int col)
{
  table_col_rem(t, col);
  t->cols_len--;

  if(!(table_get_column_length(t) % t->col_block))
  {
    table_remove_column_block(t);
  }

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
void table_remove_column_block(table *t)
{
  int num_rows, row;

  t->cols_allocated -= t->col_block;
  t->cols = realloc(t->cols, sizeof(table_column) * t->cols_allocated);

  num_rows = table_get_row_length(t);
  for (row = 0; row < num_rows; row++)
  {
    table_row *row_ptr = table_get_row_ptr(t, row);
    row_ptr->cells = realloc(row_ptr->cells, sizeof(table_cell) * t->cols_allocated);
  }
}

/**
 * \brief Add a block of columns
 * \param[out] table The table to be acted on
 */
void table_add_column_block(table *t)
{
  int num_rows, row;

  t->cols_allocated += t->col_block;
  t->cols = realloc(t->cols, sizeof(table_column) * t->cols_allocated);

  num_rows = table_get_row_length(t);
  for (row = 0; row < num_rows; row++)
  {
    table_row *row_ptr = table_get_row_ptr(t, row);
    row_ptr->cells = realloc(row_ptr->cells, sizeof(table_cell) * t->cols_allocated);
  }

}

/**
 * \brief Sets the values of the next column
 * \param[out] t The table to be acted on
 * \param[in] name The column name
 * \param[in] type The table data type
 * \return A return code
 */
int table_col_add(table *t, const char *name, table_data_type type)
{
  int num_rows, num_cols, i;
  size_t mem_size;

  mem_size = strlen(name);

  num_rows = table_get_row_length(t);
  num_cols = table_get_column_length(t);

  table_column *col_ptr = table_get_col_ptr(t, num_cols);

  col_ptr->name = malloc(sizeof(char) * mem_size + sizeof(char));

  if(!col_ptr->name)
  {
    return -1;
  }

  strcpy(col_ptr->name, name);
  col_ptr->type  = type;

  for(i = 0; i < num_rows; i++)
  {
    table_cell* cell_ptr = table_get_cell_ptr(t, i, num_cols);
    cell_ptr->value = NULL;
  }

  return 0;
}

/**
 * \brief Removes a row from the table
 * \return The corresponding int
 */
int table_col_rem(table *t, int col_num)
{
  table_column *col;
  int num_cols, num_rows, i;

  col = table_get_col_ptr(t, col_num);
  if(col->name)
  {
    free(col->name);
  }

  num_cols = table_get_column_length(t);
  for(i = col_num; i < (num_cols - 1); i++)
  {
    memcpy(t->cols + i, t->cols + i + 1, sizeof(table_column));
  }

  /* Free extraneous cell values */
  num_rows = table_get_row_length(t);
  for(i = 0; i < num_rows; i++)
  {
    table_row* row;
    table_cell* cell;
    int j;
    cell = table_get_cell_ptr(t, i, col_num);

    if(cell->value)
    {
      free(cell->value);
    }

    /* Shift cells and overwrite deleted cell */
    row = table_get_row_ptr(t, i);
    for(j = col_num; j < (num_cols - 1); j++)
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
  return t->cols + col;
}
