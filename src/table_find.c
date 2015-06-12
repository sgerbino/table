#include "table_private.h"

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
        if(table_get_bool(t, i, col) == *(bool*)value)
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
        if(table_get_bool(t, i, col) == *(bool*)value)
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
int table_find_bool(table *t, int col, bool value, table_order dir)
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

int table_sorted_find(table *t, int col, void *value, table_position position)
{
  return table_sorted_subset_find(t, col, value, position, 0, table_get_row_length(t) - 1);
}

int table_sorted_subset_find(table *t, int col, void *value, table_position position, int minimum, int maximum)
{
  table_column *column = table_get_col_ptr(t, col);
  int middle = (maximum - minimum / 2) + minimum;
  int compare = column->compare(value, table_get(t, middle, col));

  if (minimum == maximum)
    return -1;

  switch (compare)
  {
    case 0:
    {
      do
      {
        if (position == TABLE_FIRST)
          compare = column->compare(table_get(t, --middle, col), value);
        else
          compare = column->compare(table_get(t, ++middle, col), value);
      } while (!compare);
      if (position == TABLE_FIRST)
        return ++middle;
      else
        return --middle;
    }
    break;
    case 1:
      return table_sorted_subset_find(t, col, value, position, middle, maximum);
      break;
    case -1:
      return table_sorted_subset_find(t, col, value, position, minimum, middle - 1);
      break;
  }
  return -1;
}
