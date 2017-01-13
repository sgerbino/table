/**
 * \file
 * \brief The table cell implementation file
 * 
 * This file handles table cell implementations.
 */
#include "table_defs.h"

/**
 * \brief Initialize a table cell
 * \param[in] t The table
 * \param[in] row_index The table row
 * \param[in] column_index The table column
 */
void table_cell_init(table *t, int row_index, int column_index)
{
  table_cell *cell = table_get_cell_ptr(t, row_index, column_index);
  cell->value = NULL;
}

/**
 * \brief Destroy a table cell
 * \param[out] t The table
 * \param[in] row_index The table row
 * \param[out] column_index The table column
 */
void table_cell_destroy(table *t, int row_index, int column_index)
{
  table_cell *cell = NULL;
  
  switch (table_get_column_data_type(t, column_index))
  {
    case TABLE_PTR:
      break;
    default:
      cell = table_get_cell_ptr(t, row_index, column_index);
      if(cell->value)
        free(cell->value);
      break;
  }
}

/**
 * \brief Fill the buffer with the contents of a cell
 * \param[in] t The table to be examined
 * \param[in] row The row number
 * \param[in] col The column number
 * \param[out] buf The output buffer
 * \param[in] size The buffer size
 * \return A corresponding int
 */
int table_cell_to_buffer(const table *t, int row, int col, char *buf, size_t size)
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
     snprintf(buf, size, TABLE_BOOLF, table_get_bool(t, row, col));
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
 * \brief Populate the cell from the buffer
 * \param[in] t The table to be modified
 * \param[in] row The row number
 * \param[in] col The column number
 * \param[in] buf The input buffer
 * \return A corresponding int
 */
int table_cell_from_buffer(table *t, int row, int col, const char *buf)
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
      int scan_ret = sscanf(buf, TABLE_BOOLSF, &b);
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

/**
 * \brief Get the pointer of a particular cell
 * \param[in] t The table
 * \param[in] row_index The table row
 * \param[in] column_index The table column
 * \return The table cell pointer
 */
table_cell* table_get_cell_ptr(const table *t, int row_index, int column_index)
{
  table_row *row_ptr = table_get_row_ptr(t, row_index);
  return row_ptr->cells + column_index;
}
