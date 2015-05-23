#include "table_private.h"

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
        cell_ptr->value = malloc(sizeof(bool));
      }

      if(cell_ptr->value)
      {
        memcpy(cell_ptr->value, value, sizeof(bool));
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
int table_set_bool(table *t, int row, int col, bool value)
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
