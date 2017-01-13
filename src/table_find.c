/**
 * \file
 * \brief The table find implementation file
 * 
 * This file handles table find implementations.
 */
#include "table_defs.h"

/**
 * \brief Find a value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] data_type The table data data_type
 * \param[in] order The order in which to linear search the table
 * \param[in] minimum_index The lowest index to consider while searching
 * \param[in] maximum_index The highest index to consider while searching
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_subset_find(const table *t, int column_index, void* value, table_order order, int minimum_index, int maximum_index)
{
  table_comparator compare = table_get_column_compare_function(t, column_index);
  
  if (order == TABLE_ASCENDING)
  {
    for (int row_index = minimum_index; row_index <= maximum_index; row_index++)
      if (!compare(value, table_get(t, row_index, column_index)))
        return row_index;
  }
  else
  {
    for (int row_index = maximum_index; row_index >= minimum_index; row_index--)
      if (!compare(value, table_get(t, row_index, column_index)))
        return row_index;
  }
  
  return TABLE_INDEX_NOT_FOUND;
}

/**
 * \brief Find a value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find(const table* t, int column_index, void* value, table_order order)
{
  return table_subset_find(t, column_index, value, order, 0, table_get_row_length(t) - 1);
}

/**
 * \brief Find a boolean value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_bool(const table *t, int column_index, bool value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an integer value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_int(const table *t, int column_index, int value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an unsigned integer in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_uint(const table *t, int column_index, unsigned int value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an int8 value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_int8(const table *t, int column_index, int8_t value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an uint8 in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_uint8(const table *t, int column_index, uint8_t value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an int16 value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_int16(const table *t, int column_index, int16_t value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an uint16 in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_uint16(const table *t, int column_index, uint16_t value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an int32 value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_int32(const table *t, int column_index, int32_t value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an uint32 in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_uint32(const table *t, int column_index, uint32_t value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an int64 value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_int64(const table *t, int column_index, int64_t value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an uint64 in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_uint64(const table *t, int column_index, uint64_t value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a short in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_short(const table *t, int column_index, short value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an unsigned short value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_ushort(const table *t, int column_index, unsigned short value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a long value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_long(const table *t, int column_index, long value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an unsigned long value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_ulong(const table *t, int column_index, unsigned long value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a long long value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_llong(const table *t, int column_index, long long value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an unsigned long long value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_ullong(const table *t, int column_index, unsigned long long value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a float value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_float(const table *t, int column_index, float value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a double value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_double(const table *t, int column_index, double value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a long double value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_ldouble(const table *t, int column_index, long double value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a char value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_char(const table *t, int column_index, char value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find an unsigned char value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_uchar(const table *t, int column_index, unsigned char value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a string value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_string(const table *t, int column_index, const char *value, table_order order)
{
  return table_find(t, column_index, (void*)&value, order);
}

/**
 * \brief Find a pointer value in the table
 * \param[in] t The table
 * \param[in] column_index The column to search
 * \param[in] value The value to search for
 * \param[in] order The order in which to linear search the table
 * \return The row of the first occurrence of the search value or TABLE_INDEX_NOT_FOUND
 */
int table_find_ptr(const table *t, int column_index, void* value, table_order order)
{
  return table_find(t, column_index, value, order);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find(const table *t, int col, void *value, table_position position)
{
  return table_sorted_subset_find(t, col, value, position, 0, table_get_row_length(t) - 1);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The lowest row to consider
 * \param[in] maximum The highest row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find(const table *t, int col, void *value, table_position position, int minimum, int maximum)
{
  table_comparator func = table_get_column_compare_function(t, col);
  int middle = (maximum - minimum) / 2 + minimum;
  int compare = func(value, table_get(t, middle, col));

  if (minimum > maximum)
    return -middle;

  switch (compare)
  {
    case 0:
      do
      {
        if (position == TABLE_FIRST)
          compare = func(table_get(t, --middle, col), value);
        else
          compare = func(table_get(t, ++middle, col), value);
      } while (!compare);
      if (position == TABLE_FIRST)
        return ++middle;
      else
        return --middle;
      break;
    case 1:
      return table_sorted_subset_find(t, col, value, position, middle, maximum);
      break;
    case -1:
      return table_sorted_subset_find(t, col, value, position, minimum, middle - 1);
      break;
  }
  
  return -middle;
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_int(const table *t, int col, int value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_uint(const table *t, int col, unsigned int value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_int8(const table *t, int col, int8_t value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_uint8(const table *t, int col, uint8_t value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_int16(const table *t, int col, int16_t value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_uint16(const table *t, int col, uint16_t value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_int32(const table *t, int col, int32_t value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_uint32(const table *t, int col, uint32_t value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_int64(const table *t, int col, int64_t value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_uint64(const table *t, int col, uint64_t value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_short(const table *t, int col, short value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_ushort(const table *t, int col, unsigned short value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_long(const table *t, int col, long value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_ulong(const table *t, int col, unsigned long value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_llong(const table *t, int col, long long value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_ullong(const table *t, int col, unsigned long long value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_float(const table *t, int col, float value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_double(const table *t, int col, double value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_ldouble(const table *t, int col, long double value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_char(const table *t, int col, char value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_uchar(const table *t, int col, unsigned char value, table_position position)
{
   return table_sorted_find(t, col, (void*)&value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_string(const table *t, int col, const char *value, table_position position)
{
   return table_sorted_find(t, col, (void*)value, position);
}

/**
 * \brief Search through the entire table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \return The row matching given criteria
 */
int table_sorted_find_ptr(const table *t, int col, void *value, table_position position)
{
   return table_sorted_find(t, col, value, position);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_int(const table *t, int col, int value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_uint(const table *t, int col, unsigned int value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_int8(const table *t, int col, int8_t value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_uint8(const table *t, int col, uint8_t value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_int16(const table *t, int col, int16_t value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_uint16(const table *t, int col, uint16_t value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_int32(const table *t, int col, int32_t value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_uint32(const table *t, int col, uint32_t value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_int64(const table *t, int col, int64_t value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_uint64(const table *t, int col, uint64_t value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_short(const table *t, int col, short value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_ushort(const table *t, int col, unsigned short value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_long(const table *t, int col, long value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_ulong(const table *t, int col, unsigned long value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_llong(const table *t, int col, long long value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_ullong(const table *t, int col, unsigned long long value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_float(const table *t, int col, float value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_double(const table *t, int col, double value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_ldouble(const table *t, int col, long double value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_char(const table *t, int col, char value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_uchar(const table *t, int col, unsigned char value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)&value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_string(const table *t, int col, const char *value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, (void*)value, position, minimum, maximum);
}

/**
 * \brief Search through a subset of the table on a particular column using a binary search
 * \param[in] t The table
 * \param[in] col The column to search
 * \param[in] value The value to match on
 * \param[in] position The location of the returned row if there are more than one result
 * \param[in] minimum The first row to consider
 * \param[in] maximum The last row to consider
 * \return The row matching given criteria
 */
int table_sorted_subset_find_ptr(const table *t, int col, void *value, table_position position, int minimum, int maximum)
{
   return table_sorted_subset_find(t, col, value, position, minimum, maximum);
}
