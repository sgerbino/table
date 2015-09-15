#include "table_defs.h"

static void table_add_row_block(table *t);
static void table_remove_row_block(table *t);
static int table_row_add(table *t);
static int table_row_rem(table *t, int row_num);

/**
 * \brief Get the number of rows in the table
 * \param[in] table The table to examine
 * \return The number of rows
 */
int table_get_row_length(table *t)
{
  return t->rows_len;
}

/**
 * \brief Add a new row to the table
 * \param[in] t The table to be acted on
 * \return The row number
 */
int table_add_row(table *t)
{
  if(!(table_get_row_length(t) % t->row_block))
  {
    table_add_row_block(t);
  }
  table_row_add(t);
  table_notify(t, t->rows_len, -1, TABLE_ROW_ADDED);
  return t->rows_len++;
}

/**
 * \brief Delete a row from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \return A corresponding int
 */
int table_remove_row(table *t, int row)
{
  table_row_rem(t, row);
  t->rows_len--;
  if(!(table_get_row_length(t) % t->row_block))
  {
    table_remove_row_block(t);
  }
  table_notify(t, row, -1, TABLE_ROW_REMOVED);
  return 0;
}

/**
 * \brief Add a block of rows
 * \param[in] table The table
 */
static void table_add_row_block(table *t)
{
  t->rows_allocated += t->row_block;
  t->rows = realloc(t->rows, sizeof(table_row) * t->rows_allocated);
}

/**
 * \brief Remove a block of rows
 * \param[in] table The table
 */
static void table_remove_row_block(table *t)
{
  t->rows_allocated -= t->row_block;
  t->rows = realloc(t->rows, sizeof(table_row) * t->rows_allocated);
}

/**
 * \brief Sets the values of the next row
 * \param[out] t The table to be acted on
 * \return A return code
 */
static int table_row_add(table *t)
{
  int num_cols, num_rows, i;
  table_row* row;

  num_rows = table_get_row_length(t);
  num_cols = table_get_column_length(t);

  row = table_get_row_ptr(t, num_rows);

  row->cells = malloc(sizeof(table_cell) * t->cols_allocated);

  if(!row->cells)
  {
    return -1;
  }

  for(i = 0; i < num_cols; i++)
  {
    table_cell* cell;
    cell = table_get_cell_ptr(t, num_rows, i);
    cell->value = NULL;
  }

  return 0;
}

/**
 * \brief Removes a row from the table
 * \param[out] t The table to be acted on
 * \param[in] row_num The row number
 * \return A return code
 */
static int table_row_rem(table *t, int row_num)
{
  table_row* row;
  int num_rows, num_cols, i;

  num_rows = table_get_row_length(t);
  num_cols = table_get_column_length(t);

  /* Free the cell values of the row to be deleted */
  for(i = 0; i < num_cols; i++)
  {
    table_data_type type;
    table_cell* cell;
    type = table_get_column_data_type(t, i);

    /* We skip columns that are of TABLE_PTR type */
    if(type == TABLE_PTR)
    {
      continue;
    }

    cell = table_get_cell_ptr(t, row_num, i);
    if(cell->value)
    {
      free(cell->value);
    }
  }

  /* Free the cells */
  row = table_get_row_ptr(t, row_num);
  if(row->cells)
  {
    free(row->cells);
  }

  /* Shift rows up and overwrite the deleted row */
  for(i = row_num; i < (num_rows - 1); i++)
  {
    memcpy(t->rows + i, t->rows + i + 1, sizeof(table_row));
  }

  return 0;
}

/**
 * \brief Get the pointer of a particular row
 * \return The table row pointer
 */
table_row* table_get_row_ptr(table *t, int row)
{
  return t->rows + row;
}

/**
 * \brief Set the pointer of a selected row
 * \param[in] row The row index of the row to be set
 * \param[in] row_ptr The table_row pointer to set as the specified row
 */
void table_set_row_ptr(table *t, int row, table_row *row_ptr)
{
	t->rows[row] = *row_ptr;
}
