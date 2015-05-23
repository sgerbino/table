#include <table.h>
#include "table_private.h"

/**
 * \brief Return a fully constructed table pointer
 * \return A table pointer ready for usage
 */
table *table_new(void)
{
  table *t = malloc(sizeof(*t));
  table_init(t);
  return t;
}

/**
 * \brief Delete a dynamically allocated table
 */
void table_delete(void *t)
{
  table_destroy(t);
  free(t);
}

/**
 * \brief Initialize a table
 * \param[in] table The table to be initialized
 */
void table_init(table *t)
{
  /* Columns */
  t->cols = NULL;
  t->cols_len = 0;
  t->cols_allocated = 0;
  t->col_block = 10; /* Column block defaults to 10 */

  /* Rows */
  t->rows = NULL;
  t->rows_len = 0;
  t->rows_allocated = 0;
  t->row_block = 20; /* Row block defaults to 20 */

  /* Callbacks */
  t->callback = NULL;
  t->callback_data = NULL;
  t->callback_registration = NULL;
  t->callback_len = 0;
  t->callbacks_allocated = 0;
  t->callback_block = 10; /* Callback block defaults to 10 */
}

/**
 * \brief Free the tables allocated memory
 * \param[in] table The table to be freed
 */
void table_destroy(table *t)
{
  int num_rows, num_cols, i, j;

  if (!t)
    return;

  num_rows = table_get_row_length(t);
  num_cols = table_get_column_length(t);

  /* Free rows and cells */
  for(i = 0; i < num_rows; i++)
  {
    table_row* row;

    row = table_get_row_ptr(t, i);

    for(j = 0; j < num_cols; j++)
    {
      table_cell* cell;

      /* Do NOT free what table pointers point to */
      if(table_get_column_data_type(t, j) == TABLE_PTR)
      {
        continue;
      }

      cell = table_get_cell_ptr(t, i, j);

      if(cell->value)
      {
        free(cell->value);
      }
    }

    if(row->cells)
    {
      free(row->cells);
    }
  }

  if(t->rows)
  {
    free(t->rows);
  }

  /* Free columns */
  for(i = 0; i < num_cols; i++)
  {
    table_column *col;

    col = table_get_col_ptr(t, i);

    if(col->name)
    {
      free(col->name);
    }
  }

  if(t->cols)
  {
    free(t->cols);
  }

  if(t->callback)
  {
    free(t->callback);
  }

  if(t->callback_data)
  {
    free(t->callback_data);
  }
}

/**
 * \brief Duplicates a table
 * \return A duplicate table
 */
table *table_dupe(table *t)
{
  int num_rows, num_cols;
  int i, j;
  table *return_table;

  num_rows = table_get_row_length(t);
  num_cols = table_get_column_length(t);

  return_table = table_new();

  /* Copy column data */
  for(i = 0; i < num_cols; i++)
  {
    table_data_type type;
    const char *name;

    name = table_get_column_name(t, i);
    type = table_get_column_data_type(t, i);

    table_add_column(return_table, name, type);
  }

  /* Copy data */
  for(i = 0; i < num_rows; i++)
  {
    table_add_row(return_table);
    for(j = 0; j < num_cols; j++)
    {
      switch(table_get_column_data_type(t, j))
      {
      case TABLE_INT:
        {
          int val;
          val = table_get_int(t, i, j);
          table_set_int(return_table, i, j, val);
        }
        break;
      case TABLE_UINT:
        {
          unsigned int val;
          val = table_get_uint(t, i, j);
          table_set_uint(return_table, i, j, val);
        }
        break;
      case TABLE_INT8:
        {
          int8_t val;
          val = table_get_int8(t, i, j);
          table_set_int8(return_table, i, j, val);
        }
        break;
      case TABLE_UINT8:
        {
          uint8_t val;
          val = table_get_uint8(t, i, j);
          table_set_uint8(return_table, i, j, val);
        }
        break;
      case TABLE_INT16:
        {
          int16_t val;
          val = table_get_int16(t, i, j);
          table_set_int16(return_table, i, j, val);
        }
        break;
      case TABLE_UINT16:
        {
          uint16_t val;
          val = table_get_uint16(t, i, j);
          table_set_uint16(return_table, i, j, val);
        }
        break;
      case TABLE_INT32:
        {
          int32_t val;
          val = table_get_int32(t, i, j);
          table_set_int32(return_table, i, j, val);
        }
        break;
      case TABLE_UINT32:
        {
          uint32_t val;
          val = table_get_uint32(t, i, j);
          table_set_uint32(return_table, i, j, val);
        }
        break;
      case TABLE_INT64:
        {
          int64_t val;
          val = table_get_int64(t, i, j);
          table_set_int64(return_table, i, j, val);
        }
        break;
      case TABLE_UINT64:
        {
          uint64_t val;
          val = table_get_uint64(t, i, j);
          table_set_uint64(return_table, i, j, val);
        }
        break;
      case TABLE_SHORT:
        {
          short val;
          val = table_get_short(t, i, j);
          table_set_short(return_table, i, j, val);
        }
        break;
      case TABLE_USHORT:
        {
          unsigned short val;
          val = table_get_ushort(t, i, j);
          table_set_ushort(return_table, i, j, val);
        }
        break;
      case TABLE_LONG:
        {
          long val;
          val = table_get_long(t, i, j);
          table_set_long(return_table, i, j, val);
        }
        break;
      case TABLE_ULONG:
        {
          unsigned long val;
          val = table_get_ulong(t, i, j);
          table_set_ulong(return_table, i, j, val);
        }
        break;
      case TABLE_LLONG:
        {
          long long val;
          val = table_get_llong(t, i, j);
          table_set_llong(return_table, i, j, val);
        }
        break;
      case TABLE_ULLONG:
        {
          unsigned long long val;
          val = table_get_ullong(t, i, j);
          table_set_ullong(return_table, i, j, val);
        }
        break;
      case TABLE_STRING:
        {
          const char *val;
          val = table_get_string(t, i, j);
          table_set_string(return_table, i, j, val);
        }
        break;
      case TABLE_FLOAT:
        {
          float val;
          val = table_get_float(t, i, j);
          table_set_float(return_table, i, j, val);
        }
        break;
      case TABLE_DOUBLE:
        {
          double val;
          val = table_get_double(t, i, j);
          table_set_double(return_table, i, j, val);
        }
        break;
      case TABLE_LDOUBLE:
        {
          long double val;
          val = table_get_ldouble(t, i, j);
          table_set_ldouble(return_table, i, j, val);
        }
        break;
      case TABLE_BOOL:
        {
          bool val;
          val = table_get_bool(t, i, j);
          table_set_bool(return_table, i, j, val);
        }
        break;
      case TABLE_CHAR:
        {
          char val;
          val = table_get_char(t, i, j);
          table_set_char(return_table, i, j, val);
        }
        break;
      case TABLE_UCHAR:
        {
          unsigned char val;
          val = table_get_uchar(t, i, j);
          table_set_uchar(return_table, i, j, val);
        }
        break;
      case TABLE_PTR:
        {
          void* val;
          val = table_get_ptr(t, i, j);
          table_set_ptr(return_table, i, j, (void*)&val);
        }
        break;
      }
    }
  }
  return return_table;
}
