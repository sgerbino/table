#include "table_private.h"

/**
 * \brief Determine if a column is valid
 * \param t The table to be examined
 * \param col The column number
 * \return TRUE or FALSE
 */
int table_column_is_valid(table *t, int col)
{
  int retval = 0;

  if(t)
  {
    int num_cols = table_get_column_length(t);

    if(col >= 0 && col < num_cols)
    {
      retval = 1;
    }
  }

  return retval;
}

/**
 * \brief Determine if a row is valid
 * \param t The table to be examined
 * \param row The row number
 * \return TRUE or FALSE
 */
int table_row_is_valid(table *t, int row)
{
  int retval = 0;

  if(t)
  {
    int num_rows = table_get_row_length(t);

    if(row >= 0 && row < num_rows)
    {
      retval = 1;
    }
  }

  return retval;
}

/**
 * \brief Determine if a cell is valid
 * \param t The table to be examined
 * \param row The row number
 * \param col The column number
 * \return TRUE or FALSE
 */
int table_cell_is_valid(table *t, int row, int col)
{
  int retval = 0;

  if(table_column_is_valid(t, col) && table_row_is_valid(t, row))
  {
    retval = 1;
  }

  return retval;
}

/**
 * \brief Determine if a cell has a value
 * \param t The table to be examined
 * \param row The row number
 * \param col The column number
 * \return TRUE or FALSE
 */
int table_cell_has_value(table *t, int row, int col)
{
  table_cell* cell = table_get_cell_ptr(t, row, col);
  int retval = 0;

  if(cell)
  {
    if(cell->value)
    {
      retval = 1;
    }
  }

  return retval;
}
