#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <table.h>

/* Print formatters */
#define TABLE_CHARF    "%c"
#define TABLE_UCHARF   "%c"
#define TABLE_STRINGF  "%s"
#define TABLE_PTRF     "%p"
#define TABLE_SHORTF   "%hd"
#define TABLE_USHORTF  "%hu"
#define TABLE_INTF     "%d"
#define TABLE_UINTF    "%u"
#define TABLE_INT8F    "%"PRId8
#define TABLE_UINT8F   "%"PRIu8
#define TABLE_INT16F   "%"PRId16
#define TABLE_UINT16F  "%"PRIu16
#define TABLE_INT32F   "%"PRId32
#define TABLE_UINT32F  "%"PRIu32
#define TABLE_INT64F   "%"PRId64
#define TABLE_UINT64F  "%"PRIu64
#define TABLE_FLOATF   "%g"
#define TABLE_DOUBLEF  "%lf"
#define TABLE_LDOUBLEF "%Lg"
#define TABLE_LONGF    "%ld"
#define TABLE_ULONGF   "%lu"
#define TABLE_LLONGF   "%lld"
#define TABLE_ULLONGF  "%llu"

/* Scan formatters */
#define TABLE_CHARSF    TABLE_CHARF
#define TABLE_UCHARSF   TABLE_UCHARF
#define TABLE_STRINGSF  TABLE_STRINGF
#define TABLE_PTRSF     TABLE_PTRF
#define TABLE_SHORTSF   TABLE_SHORTF
#define TABLE_USHORTSF  TABLE_USHORTF
#define TABLE_INTSF     TABLE_INTF
#define TABLE_UINTSF    TABLE_UINTF
#define TABLE_INT8SF    "%"SCNd8
#define TABLE_UINT8SF   "%"SCNu8
#define TABLE_INT16SF   "%"SCNd16
#define TABLE_UINT16SF  "%"SCNu16
#define TABLE_INT32SF   "%"SCNd32
#define TABLE_UINT32SF  "%"SCNu32
#define TABLE_INT64SF   "%"SCNd64
#define TABLE_UINT64SF  "%"SCNu64
#define TABLE_FLOATSF   TABLE_FLOATF
#define TABLE_DOUBLESF  TABLE_DOUBLEF
#define TABLE_LDOUBLESF TABLE_LDOUBLEF
#define TABLE_LONGSF    TABLE_LONGF
#define TABLE_ULONGSF   TABLE_ULONGF
#define TABLE_LLONGSF   TABLE_LLONGF
#define TABLE_ULLONGSF  TABLE_ULLONGF

/* Static functions */
static void table_add_row_block(table *t);
static void table_remove_row_block(table *t);
static void table_add_column_block(table *t);
static void table_remove_column_block(table *t);

static int table_col_add(table *t, const char *name, table_data_type data_type);
static int table_col_rem(table *t, int col_num);
static int table_row_add(table *t);
static int table_row_rem(table *t, int row_num);

static table_row *table_get_row_ptr(table *t, int row_num);
static table_column *table_get_col_ptr(table *t, int col_num);
static table_cell *table_get_cell_ptr(table *t, int row_num, int col_num);

static void table_notify(table *t, int row, int col, table_event_type event_type);

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
 * \brief Get the number of rows in the table
 * \param[in] table The table to examine
 * \return The number of rows
 */
int table_get_row_length(table *t)
{
  return t->rows_len;
}

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
 * \brief Set a cell value in the table
 * \param[in] table The table to be modified
 * \param[in] row The row number
 * \param[in] col The column number
 * \param[in] value The new cell value
 * \param[in] col_type The column data type
 * \return A corresponding int
 */
int table_set(table *t, int row, int col, void *value, table_data_type col_type)
{
  int retval = -1;
  table_cell *cell_ptr = table_get_cell_ptr(t, row, col);
  table_column *col_data_ptr = table_get_col_ptr(t, col);

  switch(col_type)
  {
  case TABLE_BOOL:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(int));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(int));
        retval = 0;
      }
    }
    break;
  case TABLE_INT:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(int));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(int));
        retval = 0;
      }
    }
    break;
  case TABLE_UINT:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(unsigned int));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(unsigned int));
        retval = 0;
      }
    }
    break;
  case TABLE_INT8:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(int8_t));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(int8_t));
        retval = 0;
      }
    }
    break;
  case TABLE_UINT8:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(uint8_t));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(uint8_t));
        retval = 0;
      }
    }
    break;
  case TABLE_INT16:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(int16_t));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(int16_t));
        retval = 0;
      }
    }
    break;
  case TABLE_UINT16:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(uint16_t));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(uint16_t));
        retval = 0;
      }
    }
    break;
  case TABLE_INT32:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(int32_t));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(int32_t));
        retval = 0;
      }
    }
    break;
  case TABLE_UINT32:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(uint32_t));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(uint32_t));
        retval = 0;
      }
    }
    break;
  case TABLE_INT64:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(int64_t));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(int64_t));
        retval = 0;
      }
    }
    break;
  case TABLE_UINT64:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(uint64_t));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(uint64_t));
        retval = 0;
      }
    }
    break;
  case TABLE_SHORT:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(short));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(short));
        retval = 0;
      }
    }
    break;
  case TABLE_USHORT:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(unsigned short));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(unsigned short));
        retval = 0;
      }
    }
    break;
  case TABLE_LONG:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(long));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(long));
        retval = 0;
      }
    }
    break;
  case TABLE_ULONG:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(unsigned long));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(unsigned long));
        retval = 0;
      }
    }
    break;
  case TABLE_LLONG:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(long long));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(long long));
        retval = 0;
      }
    }
    break;
  case TABLE_ULLONG:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(unsigned long long));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(unsigned long long));
        retval = 0;
      }
    }
    break;
  case TABLE_FLOAT:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(float));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(float));
        retval = 0;
      }
    }
    break;
  case TABLE_DOUBLE:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(double));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(double));
        retval = 0;
      }
    }
    break;
  case TABLE_LDOUBLE:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(long double));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(long double));
        retval = 0;
      }
    }
    break;
  case TABLE_STRING:
    if(col_data_ptr->type == col_type)
    {
      size_t size = strlen(value);
      cell_ptr->value = realloc(cell_ptr->value, size + 1);

      if(cell_ptr->value)
      {
        strcpy(cell_ptr->value, value);
        retval = 0;
      }
    }
    break;
  case TABLE_CHAR:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(char));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(char));
        retval = 0;
      }
    }
    break;
  case TABLE_UCHAR:
    if(col_data_ptr->type == col_type)
    {
      if(!cell_ptr->value)
      {
        cell_ptr->value = malloc(sizeof(unsigned char));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(unsigned char));
        retval = 0;
      }
    }
    break;
  case TABLE_PTR:
    if(col_data_ptr->type == col_type)
    {
      cell_ptr->value = value;
      retval = 0;
    }
    break;
  }

  if(0 == retval)
  {
    table_notify(t, row, col, TABLE_DATA_MODIFIED);
  }

  return retval;
}

/**
 * \brief Set a boolean value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The boolean value
 * \return The return code
 */
int table_set_bool(table *t, int row, int col, int value)
{
  return table_set(t, row, col, (void*)&value, TABLE_BOOL);
}

/**
 * \brief Set an integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The integer value
 * \return The return code
 */
int table_set_int(table *t, int row, int col, int value)
{
  return table_set(t, row, col, (void*)&value, TABLE_INT);
}

/**
 * \brief Set an unsigned integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned integer value
 * \return The return code
 */
int table_set_uint(table *t, int row, int col, unsigned int value)
{
  return table_set(t, row, col, (void*)&value, TABLE_UINT);
}

/**
 * \brief Set an 8-bit integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The 8-bit integer value
 * \return The return code
 */
int table_set_int8(table *t, int row, int col, int8_t value)
{
  return table_set(t, row, col, (void*)&value, TABLE_INT8);
}

/**
 * \brief Set an unsigned 8-bit integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned 8-bit integer value
 * \return The return code
 */
int table_set_uint8(table *t, int row, int col, uint8_t value)
{
  return table_set(t, row, col, (void*)&value, TABLE_UINT8);
}

/**
 * \brief Set a 16-bit integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The 16-bit integer value
 * \return The return code
 */
int table_set_int16(table *t, int row, int col, int16_t value)
{
  return table_set(t, row, col, (void*)&value, TABLE_INT16);
}

/**
 * \brief Set an unsigned 16-bit integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned 16-bit integer value
 * \return The return code
 */
int table_set_uint16(table *t, int row, int col, uint16_t value)
{
  return table_set(t, row, col, (void*)&value, TABLE_UINT16);
}

/**
 * \brief Set a 32-bit integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The 32-bit integer value
 * \return The return code
 */
int table_set_int32(table *t, int row, int col, int32_t value)
{
  return table_set(t, row, col, (void*)&value, TABLE_INT32);
}

/**
 * \brief Set an unsigned 32-bit integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned 32-bit integer value
 * \return The return code
 */
int table_set_uint32(table *t, int row, int col, uint32_t value)
{
  return table_set(t, row, col, (void*)&value, TABLE_UINT32);
}

/**
 * \brief Set a 64-bit integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The 64-bit integer value
 * \return The return code
 */
int table_set_int64(table *t, int row, int col, int64_t value)
{
  return table_set(t, row, col, (void*)&value, TABLE_INT64);
}

/**
 * \brief Set an unsigned 64-bit integer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned 64-bit integer value
 * \return The return code
 */
int table_set_uint64(table *t, int row, int col, uint64_t value)
{
  return table_set(t, row, col, (void*)&value, TABLE_UINT64);
}

/**
 * \brief Set a short value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The short value
 * \return The return code
 */
int table_set_short(table *t, int row, int col, short value)
{
  return table_set(t, row, col, (void*)&value, TABLE_SHORT);
}

/**
 * \brief Set an unsigned short value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned short value
 * \return The return code
 */
int table_set_ushort(table *t, int row, int col, unsigned short value)
{
  return table_set(t, row, col, (void*)&value, TABLE_USHORT);
}

/**
 * \brief Set a long value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The long value
 * \return The return code
 */
int table_set_long(table *t, int row, int col, long value)
{
  return table_set(t, row, col, (void*)&value, TABLE_LONG);
}

/**
 * \brief Set an unsigned long value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned long value
 * \return The return code
 */
int table_set_ulong(table *t, int row, int col, unsigned long value)
{
  return table_set(t, row, col, (void*)&value, TABLE_ULONG);
}

/**
 * \brief Set a long long value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The long long value
 * \return The return code
 */
int table_set_llong(table *t, int row, int col, long long value)
{
  return table_set(t, row, col, (void*)&value, TABLE_LLONG);
}

/**
 * \brief Set an unsigned long long value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned long long value
 * \return The return code
 */
int table_set_ullong(table *t, int row, int col, unsigned long long value)
{
  return table_set(t, row, col, (void*)&value, TABLE_ULLONG);
}

/**
 * \brief Set a float value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The float value
 * \return The return code
 */
int table_set_float(table *t, int row, int col, float value)
{
  return table_set(t, row, col, (void*)&value, TABLE_FLOAT);
}

/**
 * \brief Set a double value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The double value
 * \return The return code
 */
int table_set_double(table *t, int row, int col, double value)
{
  return table_set(t, row, col, (void*)&value, TABLE_DOUBLE);
}

/**
 * \brief Set a long double value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The long double value
 * \return The return code
 */
int table_set_ldouble(table *t, int row, int col, long double value)
{
  return table_set(t, row, col, (void*)&value, TABLE_LDOUBLE);
}

/**
 * \brief Set a string value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The string value
 * \return The return code
 */
int table_set_string(table *t, int row, int col, const char* value)
{
  return table_set(t, row, col, (void*)value, TABLE_STRING);
}

/**
 * \brief Set a char value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The char value
 * \return The return code
 */
int table_set_char(table *t, int row, int col, char value)
{
  return table_set(t, row, col, (void*)&value, TABLE_CHAR);
}

/**
 * \brief Set an unsigned char value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The unsigned char value
 * \return The return code
 */
int table_set_uchar(table *t, int row, int col, unsigned char value)
{
  return table_set(t, row, col, (void*)&value, TABLE_UCHAR);
}

/**
 * \brief Set a pointer value in the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \param[in] value The pointer value
 * \return The return code
 */
int table_set_ptr(table *t, int row, int col, void* value)
{
  return table_set(t, row, col, value, TABLE_PTR);
}

/**
 * \brief Get a cells raw pointer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The cells raw pointer value
 */
void *table_get(table *t, int row, int col)
{
  return table_get_cell_ptr(t, row, col)->value;
}

/**
 * \brief Get a boolean value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The boolean value
 */
int table_get_bool(table *t, int row, int col)
{
  return *((int*)table_get(t, row, col));
}

/**
 * \brief Get an integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The integer value
 */
int table_get_int(table *t, int row, int col)
{
  return *((int*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned integer value
 */
unsigned int table_get_uint(table *t, int row, int col)
{
  return *((unsigned int*)table_get(t, row, col));
}

/**
 * \brief Get an 8-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The 8-bit integer value
 */
int8_t table_get_int8(table *t, int row, int col)
{
  return *((int8_t*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned 8-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned 8-bit integer value
 */
uint8_t table_get_uint8(table *t, int row, int col)
{
  return *((uint8_t*)table_get(t, row, col));
}

/**
 * \brief Get a 16-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The 16-bit integer value
 */
int16_t table_get_int16(table *t, int row, int col)
{
  return *((int16_t*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned 16-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned 16-bit integer value
 */
uint16_t table_get_uint16(table *t, int row, int col)
{
  return *((uint16_t*)table_get(t, row, col));
}

/**
 * \brief Get a 32-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The 32-bit integer value
 */
int32_t table_get_int32(table *t, int row, int col)
{
  return *((int32_t*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned 32-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned 32-bit integer value
 */
uint32_t table_get_uint32(table *t, int row, int col)
{
  return *((uint32_t*)table_get(t, row, col));
}

/**
 * \brief Get a 64-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The 64-bit integer value
 */
int64_t table_get_int64(table *t, int row, int col)
{
  return *((int64_t*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned 64-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned 64-bit integer value
 */
uint64_t table_get_uint64(table *t, int row, int col)
{
  return *((uint64_t*)table_get(t, row, col));
}

/**
 * \brief Get a short value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The short value
 */
short table_get_short(table *t, int row, int col)
{
  return *((short*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned short value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned short value
 */
unsigned short table_get_ushort(table *t, int row, int col)
{
  return *((unsigned short*)table_get(t, row, col));
}

/**
 * \brief Get a long value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The long value
 */
long table_get_long(table *t, int row, int col)
{
  return *((long*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned long value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned long value
 */
unsigned long table_get_ulong(table *t, int row, int col)
{
  return *((unsigned long*)table_get(t, row, col));
}

/**
 * \brief Get a long long value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The long long value
 */
long long table_get_llong(table *t, int row, int col)
{
  return *((long long*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned long long value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned long long value
 */
unsigned long long table_get_ullong(table *t, int row, int col)
{
  return *((unsigned long long*)table_get(t, row, col));
}

/**
 * \brief Get a float value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The float value
 */
float table_get_float(table *t, int row, int col)
{
  return *((float*)table_get(t, row, col));
}

/**
 * \brief Get a double value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The double value
 */
double table_get_double(table *t, int row, int col)
{
  return *((double*)table_get(t, row, col));
}

/**
 * \brief Get a long double value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The long double value
 */
long double table_get_ldouble(table *t, int row, int col)
{
  return *((long double*)table_get(t, row, col));
}

/**
 * \brief Get a char value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The char value
 */
char table_get_char(table *t, int row, int col)
{
  return *((char*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned char value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned char value
 */
unsigned char table_get_uchar(table *t, int row, int col)
{
  return *((unsigned char*)table_get(t, row, col));
}

/**
 * \brief Get a string value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The string value
 */
const char* table_get_string(table *t, int row, int col)
{
  return (const char*)table_get(t, row, col);
}

/**
 * \brief Get a pointer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The pointer value
 */
void* table_get_ptr(table *t, int row, int col)
{
  return table_get(t, row, col);
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
 * \brief Remove a block of columns
 * \param[out] table The table to be acted on
 */
static void table_remove_column_block(table *t)
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
static void table_add_column_block(table *t)
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
static int table_col_add(table *t, const char *name, table_data_type type)
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
 * \brief Removes a row from the table
 * \return The corresponding int
 */
static int table_col_rem(table *t, int col_num)
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
 * \brief Get the pointer of a particular row
 * \return The table row pointer
 */
static table_row* table_get_row_ptr(table *t, int row)
{
  return t->rows + row;
}

/**
 * \brief Get the pointer of a particular column
 * \return The table column pointer
 */
static table_column *table_get_col_ptr(table *t, int col)
{
  return t->cols + col;
}

/**
 * \brief Get the pointer of a particular cell
 * \return The table cell pointer
 */
static table_cell* table_get_cell_ptr(table *t, int row, int col)
{
  table_row *row_ptr = table_get_row_ptr(t, row);
  return row_ptr->cells + col;
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
          int val;
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

/**
 * \brief Find a value in the table
 * \return The row of the first occurrence of the search value or -1
 */
int table_find(table *t, int col, void* value, table_data_type data_type, table_order order)
{
  const char *str;
  int i, retval = -1;
  int num_rows = table_get_row_length(t);

  if(order == TABLE_ASCENDING)
  {
    for(i = 0; i < num_rows; i++)
    {
      if(retval != -1)
      {
        break;
      }

      switch(data_type)
      {
      case TABLE_INT:
        if(table_get_int(t, i, col) == *(int*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT:
        if(table_get_uint(t, i, col) == *(unsigned int*)value)
        {
          retval = i;
        }
        break;
      case TABLE_INT8:
        if(table_get_int8(t, i, col) == *(int8_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT8:
        if(table_get_uint8(t, i, col) == *(uint8_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_INT16:
        if(table_get_int16(t, i, col) == *(int16_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT16:
        if(table_get_uint16(t, i, col) == *(uint16_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_INT32:
        if(table_get_int32(t, i, col) == *(int32_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT32:
        if(table_get_uint32(t, i, col) == *(uint32_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_INT64:
        if(table_get_int64(t, i, col) == *(int64_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT64:
        if(table_get_uint64(t, i, col) == *(uint64_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_SHORT:
        if(table_get_short(t, i, col) == *(short*)value)
        {
          retval = i;
        }
        break;
      case TABLE_USHORT:
        if(table_get_ushort(t, i, col) == *(unsigned short*)value)
        {
          retval = i;
        }
        break;
      case TABLE_LONG:
        if(table_get_long(t, i, col) == *(long*)value)
        {
          retval = i;
        }
        break;
      case TABLE_ULONG:
        if(table_get_ulong(t, i, col) == *(unsigned long*)value)
        {
          retval = i;
        }
        break;
      case TABLE_LLONG:
        if(table_get_llong(t, i, col) == *(long long*)value)
        {
          retval = i;
        }
        break;
      case TABLE_ULLONG:
        if(table_get_ullong(t, i, col) == *(unsigned long long*)value)
        {
          retval = i;
        }
        break;
      case TABLE_STRING:
        str = table_get_string(t, i, col);
        if(!strcmp(str, (char*)value))
        {
          retval = i;
        }
        break;
      case TABLE_FLOAT:
        if(table_get_float(t, i, col) == *(float*)value)
        {
          retval = i;
        }
        break;
      case TABLE_DOUBLE:
        if(table_get_double(t, i, col) == *(double*)value)
        {
          retval = i;
        }
        break;
      case TABLE_LDOUBLE:
        if(table_get_ldouble(t, i, col) == *(long double*)value)
        {
          retval = i;
        }
        break;
      case TABLE_BOOL:
        if(table_get_bool(t, i, col) == *(int*)value)
        {
          retval = i;
        }
        break;
      case TABLE_CHAR:
        if(table_get_char(t, i, col) == *(char*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UCHAR:
        if(table_get_uchar(t, i, col) == *(unsigned char*)value)
        {
          retval = i;
        }
        break;
      case TABLE_PTR:
        if(table_get_ptr(t, i, col) == value)
        {
          retval = i;
        }
        break;
      }
    }
  }
  else
  {
    for(i = num_rows - 1; i >= 0; i--)
    {
      if(retval != -1)
      {
        break;
      }

      switch(data_type)
      {
      case TABLE_INT:
        if(table_get_int(t, i, col) == *(int*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT:
        if(table_get_uint(t, i, col) == *(unsigned int*)value)
        {
          retval = i;
        }
        break;
      case TABLE_INT8:
        if(table_get_int8(t, i, col) == *(int8_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT8:
        if(table_get_uint8(t, i, col) == *(uint8_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_INT16:
        if(table_get_int16(t, i, col) == *(int16_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT16:
        if(table_get_uint16(t, i, col) == *(uint16_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_INT32:
        if(table_get_int32(t, i, col) == *(int32_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT32:
        if(table_get_uint32(t, i, col) == *(uint32_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_INT64:
        if(table_get_int64(t, i, col) == *(int64_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UINT64:
        if(table_get_uint64(t, i, col) == *(uint64_t*)value)
        {
          retval = i;
        }
        break;
      case TABLE_SHORT:
        if(table_get_short(t, i, col) == *(short*)value)
        {
          retval = i;
        }
        break;
      case TABLE_USHORT:
        if(table_get_ushort(t, i, col) == *(unsigned short*)value)
        {
          retval = i;
        }
        break;
      case TABLE_LONG:
        if(table_get_long(t, i, col) == *(long*)value)
        {
          retval = i;
        }
        break;
      case TABLE_ULONG:
        if(table_get_ulong(t, i, col) == *(unsigned long*)value)
        {
          retval = i;
        }
        break;
      case TABLE_LLONG:
        if(table_get_llong(t, i, col) == *(long long*)value)
        {
          retval = i;
        }
        break;
      case TABLE_ULLONG:
        if(table_get_ullong(t, i, col) == *(unsigned long long*)value)
        {
          retval = i;
        }
        break;
      case TABLE_STRING:
        str = table_get_string(t, i, col);
        if(!strcmp(str, (const char*)value))
        {
          retval = i;
        }
        break;
      case TABLE_FLOAT:
        if(table_get_float(t, i, col) == *(float*)value)
        {
          retval = i;
        }
        break;
      case TABLE_DOUBLE:
        if(table_get_double(t, i, col) == *(double*)value)
        {
          retval = i;
        }
        break;
      case TABLE_LDOUBLE:
        if(table_get_ldouble(t, i, col) == *(long double*)value)
        {
          retval = i;
        }
        break;
      case TABLE_BOOL:
        if(table_get_bool(t, i, col) == *(int*)value)
        {
          retval = i;
        }
        break;
      case TABLE_CHAR:
        if(table_get_char(t, i, col) == *(char*)value)
        {
          retval = i;
        }
        break;
      case TABLE_UCHAR:
        if(table_get_uchar(t, i, col) == *(unsigned char*)value)
        {
          retval = i;
        }
        break;
      case TABLE_PTR:
        if(table_get_ptr(t, i, col) == value)
        {
          retval = i;
        }
        break;
      }
    }
  }

  return retval;
}

/**
 * \brief Find a boolean value in the table
 * \return The row of the first occurrence of the search value or -1
 */
int table_find_bool(table *t, int col, int value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_BOOL, dir);
}

/**
 * \brief Find an integer value in the table
 * \return The row of the first occurrence of the search value or -1
 */
int table_find_int(table *t, int col, int value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_INT, dir);
}

/**
 * \brief Find an unsigned integer in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_uint(table *t, int col, unsigned int value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_UINT, dir);
}

/**
 * \brief Find an int8 value in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_int8(table *t, int col, int8_t value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_INT8, dir);
}

/**
 * \brief Find an uint8 in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_uint8(table *t, int col, uint8_t value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_UINT8, dir);
}

/**
 * \brief Find an int16 value in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_int16(table *t, int col, int16_t value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_INT16, dir);
}

/***
 * \brief Find an uint16 in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_uint16(table *t, int col, uint16_t value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_UINT16, dir);
}

/**
 * \brief Find an int32 value in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_int32(table *t, int col, int32_t value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_INT32, dir);
}

/**
 * \brief Find an uint32 in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_uint32(table *t, int col, uint32_t value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_UINT32, dir);
}

/**
 * \brief Find an int64 value in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_int64(table *t, int col, int64_t value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_INT64, dir);
}

/**
 * \brief Find an uint64 in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_uint64(table *t, int col, uint64_t value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_UINT64, dir);
}

/**
 * \brief Find a short in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_short(table *t, int col, short value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_SHORT, dir);
}

/**
 * \brief Find an unsigned short value in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_ushort(table *t, int col, unsigned short value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_USHORT, dir);
}

/**
 * \brief Find a long value in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_long(table *t, int col, long value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_LONG, dir);
}

/**
 * \brief Find an unsigned long value in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_ulong(table *t, int col, unsigned long value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_ULONG, dir);
}

/**
 * \brief Find a long long value in the table
 * \return A row of the first occurence of the search value or -1
 */
int table_find_llong(table *t, int col, long long value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_LLONG, dir);
}

/**
 * \brief Find an unsigned long long value in the table
 * \return A row of the occurence of the search value or -1
 */
int table_find_ullong(table *t, int col, unsigned long long value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_ULLONG, dir);
}

/**
 * \brief Find a float value in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_float(table *t, int col, float value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_FLOAT, dir);
}

/**
 * \brief Find a double value in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_double(table *t, int col, double value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_DOUBLE, dir);
}

/**
 * \brief Find a long double value in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_ldouble(table *t, int col, long double value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_LDOUBLE, dir);
}

/**
 * \brief Find a char value in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_char(table *t, int col, char value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_CHAR, dir);
}

/**
 * \brief Find an unsigned char value in the table
 * \return The row of the first occurence of the search value or -1
 */
int table_find_uchar(table *t, int col, unsigned char value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_UCHAR, dir);
}

/**
 * \brief Find a string value in the table
 * \return The row containing the string
 */
int table_find_string(table *t, int col, const char *value, table_order dir)
{
  return table_find(t, col, (void*)&value, TABLE_STRING, dir);
}

/**
 * \brief Find a pointer value in the table
 * \return The row in which the pointer was found or -1 for not found
 */
int table_find_ptr(table *t, int col, void* value, table_order dir)
{
  return table_find(t, col, value, TABLE_PTR, dir);
}

/**
 * \brief Register a data callback for the table
 */
void table_register_callback(table *t, table_callback_function func, void* data, table_bitfield event_types)
{
  table_callback_function *tmp_callback;
  void **tmp_callback_data;
  table_bitfield *tmp_callback_registration;
  size_t i;

  /* Check if this callback already exists. */
  for (i = 0; i < t->callback_len; i++)
  {
    if (t->callback[i] == func && t->callback_data[i] == data)
    {
      /* Add the new event types, if any. */
      t->callback_registration[i] |= event_types;
      return;
    }
  }

  if(!(t->callback_len % t->callback_block))
  {
    tmp_callback = calloc(t->callback_len + t->callback_block, sizeof(table_callback_function));
    tmp_callback_data = calloc(t->callback_len + t->callback_block, sizeof(void*));
    tmp_callback_registration = calloc(t->callback_len + t->callback_block, sizeof(table_bitfield*));
    if(t->callback != NULL)
    {
      memcpy(tmp_callback, t->callback, t->callback_len * sizeof(table_callback_function));
      memcpy(tmp_callback_data, t->callback_data, t->callback_len * sizeof(void*));
      memcpy(tmp_callback_registration, t->callback_registration, t->callback_len * sizeof(table_bitfield*));
      free(t->callback);
      free(t->callback_data);
      free(t->callback_registration);
    }
    t->callback = tmp_callback;
    t->callback_data = tmp_callback_data;
    t->callback_registration = tmp_callback_registration;
  }
  *(t->callback + t->callback_len) = func;
  *(t->callback_data + t->callback_len) = data;
  *(t->callback_registration + t->callback_len) = event_types;
  t->callback_len++;
}

/**
 * \brief Unregister a data callback for the table
 */
void table_unregister_callback(table *t, table_callback_function func, void* data)
{
  table_callback_function *tmp_callback;
  void **tmp_callback_data;
  table_bitfield *tmp_callback_registration;
  int i, rm = -1;

  /* Find a match */
  for(i = 0; i < t->callback_len; i++)
  {
    if(t->callback[i] == func && t->callback_data[i] == data)
    {
      rm = i;
      break;
    }
  }

  /* If a match was found, shift all the cells down */
  if(rm != -1)
  {
    for(i = rm; i < t->callback_len - 1; i++)
    {
      t->callback[i] = t->callback[i + 1];
      t->callback_data[i] = t->callback_data[i + 1];
      t->callback_registration[i] = t->callback_registration[i + 1];
    }

    if(!(--t->callback_len % t->callback_block))
    {
      if(t->callback_len != 0)
      {
        tmp_callback = calloc(t->callback_len + t->callback_block, sizeof(table_callback_function));
        tmp_callback_data = calloc(t->callback_len + t->callback_block, sizeof(void*));
        tmp_callback_registration = calloc(t->callback_len + t->callback_block, sizeof(table_bitfield*));
        memcpy(tmp_callback, t->callback, t->callback_len * sizeof(table_callback_function));
        memcpy(tmp_callback_data, t->callback_data, t->callback_len * sizeof(void*));
        memcpy(tmp_callback_registration, t->callback_registration, t->callback_len * sizeof(table_bitfield*));
        free(t->callback);
        free(t->callback_data);
        free(t->callback_registration);
        t->callback = tmp_callback;
        t->callback_data = tmp_callback_data;
        t->callback_registration = tmp_callback_registration;
      }
      else
      {
        free(t->callback);
        free(t->callback_data);
        free(t->callback_registration);
        t->callback = NULL;
        t->callback_data = NULL;
        t->callback_registration = NULL;
      }
    }
  }
}

/**
 * \brief Notify registered callbacks
 * \param[in] table The table to do notifications on
 * \param[in] row The row number
 * \param[in] col The column number
 * \param[in] cb_type The callback type
 */
static void table_notify(table *t, int row, int col, table_event_type event_type)
{
  int i;
  for (i = 0; i < t->callback_len; i++)
  {
    if (t->callback_registration[i] & event_type)
    {
      t->callback[i](t, row, col, event_type, t->callback_data[i]);
    }
  }
}

/**
 * \brief Fill the string with the contents of a cell
 * \param[in] table The table to be examined
 * \param[in] row The row number
 * \param[in] col The column number
 * \param[out] buf The output buffer
 * \param[in] size The buffer size
 * \return A corresponding int
 */
int table_cell_to_string(table *t, int row, int col, char *buf, size_t size)
{
  int retcode = 0;
  switch(table_get_column_data_type(t, col))
  {
  case TABLE_INT:
    snprintf(buf, size, TABLE_INTF, table_get_int(t, row, col));
    break;
  case TABLE_UINT:
    snprintf(buf, size, TABLE_UINTF, table_get_uint(t, row, col));
    break;
  case TABLE_INT8:
    snprintf(buf, size, TABLE_INT8F, table_get_int8(t, row, col));
    break;
  case TABLE_UINT8:
    snprintf(buf, size, TABLE_UINT8F, table_get_uint8(t, row, col));
    break;
  case TABLE_INT16:
    snprintf(buf, size, TABLE_INT16F, table_get_int16(t, row, col));
    break;
  case TABLE_UINT16:
    snprintf(buf, size, TABLE_UINT16F, table_get_uint16(t, row, col));
    break;
  case TABLE_INT32:
    snprintf(buf, size, TABLE_INT32F, table_get_int32(t, row, col));
    break;
  case TABLE_UINT32:
    snprintf(buf, size, TABLE_UINT32F, table_get_uint32(t, row, col));
    break;
  case TABLE_INT64:
    snprintf(buf, size, TABLE_INT64F, table_get_int64(t, row, col));
    break;
  case TABLE_UINT64:
    snprintf(buf, size, TABLE_UINT64F, table_get_uint64(t, row, col));
    break;
  case TABLE_SHORT:
    snprintf(buf, size, TABLE_SHORTF, table_get_short(t, row, col));
    break;
  case TABLE_USHORT:
    snprintf(buf, size, TABLE_USHORTF, table_get_ushort(t, row, col));
    break;
  case TABLE_LONG:
    snprintf(buf, size, TABLE_LONGF, table_get_long(t, row, col));
    break;
  case TABLE_ULONG:
    snprintf(buf, size, TABLE_ULONGF, table_get_ulong(t, row, col));
    break;
  case TABLE_LLONG:
    snprintf(buf, size, TABLE_LLONGF, table_get_llong(t, row, col));
    break;
  case TABLE_ULLONG:
    snprintf(buf, size, TABLE_ULLONGF, table_get_ullong(t, row, col));
    break;
  case TABLE_STRING:
    snprintf(buf, size, TABLE_STRINGF, table_get_string(t, row, col));
    break;
  case TABLE_FLOAT:
    snprintf(buf, size, TABLE_FLOATF, table_get_float(t, row, col));
    break;
  case TABLE_DOUBLE:
    snprintf(buf, size, TABLE_DOUBLEF, table_get_double(t, row, col));
    break;
  case TABLE_LDOUBLE:
    snprintf(buf, size, TABLE_LDOUBLEF, table_get_ldouble(t, row, col));
    break;
  case TABLE_BOOL:
    snprintf(buf, size, TABLE_INTF, table_get_bool(t, row, col));
    break;
  case TABLE_CHAR:
    snprintf(buf, size, TABLE_CHARF, table_get_char(t, row, col));
    break;
  case TABLE_UCHAR:
    snprintf(buf, size, TABLE_UCHARF, table_get_uchar(t, row, col));
    break;
  case TABLE_PTR:
    snprintf(buf, size, TABLE_PTRF, table_get_ptr(t, row, col));
    break;
  }
  return retcode;
}

/**
 * \brief Populate the cell from the string.
 * \param[in] table The table to be modified
 * \param[in] row The row number
 * \param[in] col The column number
 * \param[in] buf The input string
 * \return A corresponding int
 */
int table_cell_from_string(table *t, int row, int col, const char *buf)
{
  int retcode = 0;
  switch(table_get_column_data_type(t, col))
  {
  case TABLE_INT:
    {
      int i;
      int scan_ret = sscanf(buf, TABLE_INTSF, &i);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_int(t, row, col, i);
      }
    }
    break;
  case TABLE_UINT:
    {
      int u;
      int scan_ret = sscanf(buf, TABLE_UINTSF, &u);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_uint(t, row, col, u);
      }
    }
    break;
  case TABLE_INT8:
    {
      int8_t i8;
      int scan_ret = sscanf(buf, TABLE_INT8SF, &i8);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_int8(t, row, col, i8);
      }
    }
    break;
  case TABLE_UINT8:
    {
      uint8_t u8;
      int scan_ret = sscanf(buf, TABLE_UINT8SF, &u8);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_uint8(t, row, col, u8);
      }
    }
    break;
  case TABLE_INT16:
    {
      int16_t i16;
      int scan_ret = sscanf(buf, TABLE_INT16SF, &i16);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_int16(t, row, col, i16);
      }
    }
    break;
  case TABLE_UINT16:
    {
      uint16_t u16;
      int scan_ret = sscanf(buf, TABLE_UINT16SF, &u16);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_uint16(t, row, col, u16);
      }
    }
    break;
  case TABLE_INT32:
    {
      int32_t i32;
      int scan_ret = sscanf(buf, TABLE_INT32SF, &i32);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_int32(t, row, col, i32);
      }
    }
    break;
  case TABLE_UINT32:
    {
      uint32_t u32;
      int scan_ret = sscanf(buf, TABLE_UINT32SF, &u32);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_uint32(t, row, col, u32);
      }
    }
    break;
  case TABLE_INT64:
    {
      int64_t i64;
      int scan_ret = sscanf(buf, TABLE_INT64SF, &i64);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_int64(t, row, col, i64);
      }
    }
    break;
  case TABLE_UINT64:
    {
      uint64_t u64;
      int scan_ret = sscanf(buf, TABLE_UINT64SF, &u64);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_uint64(t, row, col, u64);
      }
    }
    break;
  case TABLE_SHORT:
    {
      short s;
      int scan_ret = sscanf(buf, TABLE_SHORTSF, &s);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_short(t, row, col, s);
      }
    }
    break;
  case TABLE_USHORT:
    {
      unsigned short us;
      int scan_ret = sscanf(buf, TABLE_USHORTSF, &us);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_ushort(t, row, col, us);
      }
    }
    break;
  case TABLE_LONG:
    {
      long l;
      int scan_ret = sscanf(buf, TABLE_LONGSF, &l);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_long(t, row, col, l);
      }
    }
    break;
  case TABLE_ULONG:
    {
      unsigned long ul;
      int scan_ret = sscanf(buf, TABLE_ULONGSF, &ul);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_ulong(t, row, col, ul);
      }
    }
    break;
  case TABLE_LLONG:
    {
      long long ll;
      int scan_ret = sscanf(buf, TABLE_LLONGSF, &ll);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_llong(t, row, col, ll);
      }
    }
    break;
  case TABLE_ULLONG:
    {
      unsigned long long ull;
      int scan_ret = sscanf(buf, TABLE_ULLONGSF, &ull);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_ullong(t, row, col, ull);
      }
    }
    break;
  case TABLE_STRING:
    {
      char s[256];
      int scan_ret = sscanf(buf, TABLE_STRINGSF, s);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_string(t, row, col, s);
      }
    }
    break;
  case TABLE_FLOAT:
    {
      float f;
      int scan_ret = sscanf(buf, TABLE_FLOATSF, &f);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_float(t, row, col, f);
      }
    }
    break;
  case TABLE_DOUBLE:
    {
      double d;
      int scan_ret = sscanf(buf, TABLE_DOUBLESF, &d);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_double(t, row, col, d);
      }
    }
    break;
  case TABLE_LDOUBLE:
    {
      long double ld;
      int scan_ret = sscanf(buf, TABLE_LDOUBLESF, &ld);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_ldouble(t, row, col, ld);
      }
    }
    break;
  case TABLE_BOOL:
    {
      int b;
      int scan_ret = sscanf(buf, TABLE_INTSF, &b);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        if(b)
        {
          table_set_bool(t, row, col, 1);
        }
        else
        {
          table_set_bool(t, row, col, 0);
        }
      }
    }
    break;
  case TABLE_CHAR:
    {
      char c;
      int scan_ret = sscanf(buf, TABLE_CHARSF, &c);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_char(t, row, col, c);
      }
    }
    break;
  case TABLE_UCHAR:
    {
      unsigned char uc;
      int scan_ret = sscanf(buf, TABLE_UCHARSF, &uc);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_uchar(t, row, col, uc);
      }
    }
    break;
  case TABLE_PTR:
    {
      void* p;
      int scan_ret = sscanf(buf, TABLE_PTRSF, &p);
      if(-1 == scan_ret)
      {
        retcode = -1;
      }
      else if(1 != scan_ret)
      {
        retcode = -1;
      }
      else
      {
        table_set_ptr(t, row, col, p);
      }
    }
    break;
  }
  return retcode;
}

/**
 * \brief Free a table cells data and set the ponter to NULL
 * \param t Table to be acted on
 * \param row The table row
 * \param col The table column
 * \return A success code
 */
int table_cell_nullify(table *t, int row, int col)
{
  table_cell *cell = table_get_cell_ptr(t, row, col);
  if (cell->value)
  {
    free(cell->value);
    cell->value = NULL;
  }
  return 0;
}
