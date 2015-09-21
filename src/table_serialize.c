/**
 * \file
 * \brief The table serialize implementation file
 * 
 * This file handles table serialize implementations.
 */
#include "table_defs.h"

#define PACK(destination, source, type)                 \
   do {                                                 \
      *(type*)destination = *(type*)source;             \
      destination = (char*)destination + sizeof(type);  \
   } while (0)

#define PACK_STRING(destination, source, length)        \
   do {                                                 \
      strncpy(destination, source, length);             \
      destination = (char*)destination + length;        \
   } while (0)

void table_serialize(table *t, void *buf, size_t len)
{
   uint64_t row_len = table_get_row_length(t);
   uint64_t col_len = table_get_column_length(t);
   uint64_t row, col, i;

   PACK(buf, &col_len, uint64_t);
   PACK(buf, &t->column_block, uint64_t);
   for (col = 0; col < col_len; ++col)
   {
      const char *name = table_get_column_name(t, col);
      size_t name_len = strlen(name) + 1;
      table_data_type type = table_get_column_data_type(t, col);
      PACK(buf, &type, table_data_type);
      PACK_STRING(buf, name, name_len);
   }

   PACK(buf, &row_len, uint64_t);
   PACK(buf, &t->row_block, uint64_t);
   for (row = 0; row < row_len; ++row)
   {
      for (col = 0; col < col_len; ++col)
      {
         table_data_type type = table_get_column_data_type(t, col);
         switch(type)
         {
         case TABLE_BOOL:
            PACK(buf, table_get(t, row, col), bool);
            break;
         case TABLE_INT:
            PACK(buf, table_get(t, row, col), int);
            break;
         case TABLE_UINT:
            PACK(buf, table_get(t, row, col), unsigned int);
            break;
         case TABLE_INT8:
            PACK(buf, table_get(t, row, col), int8_t);
            break;
         case TABLE_UINT8:
            PACK(buf, table_get(t, row, col), uint8_t);
            break;
         case TABLE_INT16:
            PACK(buf, table_get(t, row, col), int16_t);
            break;
         case TABLE_UINT16:
            PACK(buf, table_get(t, row, col), uint16_t);
            break;
         case TABLE_INT32:
            PACK(buf, table_get(t, row, col), int32_t);
            break;
         case TABLE_UINT32:
            PACK(buf, table_get(t, row, col), uint32_t);
            break;
         case TABLE_INT64:
            PACK(buf, table_get(t, row, col), int64_t);
            break;
         case TABLE_UINT64:
            PACK(buf, table_get(t, row, col), uint64_t);
            break;
         case TABLE_SHORT:
            PACK(buf, table_get(t, row, col), short);
            break;
         case TABLE_USHORT:
            PACK(buf, table_get(t, row, col), unsigned short);
            break;
         case TABLE_LONG:
            PACK(buf, table_get(t, row, col), long);
            break;
         case TABLE_ULONG:
            PACK(buf, table_get(t, row, col), unsigned long);
            break;
         case TABLE_LLONG:
            PACK(buf, table_get(t, row, col), long long);
            break;
         case TABLE_ULLONG:
            PACK(buf, table_get(t, row, col), unsigned long long);
            break;
         case TABLE_FLOAT:
            PACK(buf, table_get(t, row, col), float);
            break;
         case TABLE_DOUBLE:
            PACK(buf, table_get(t, row, col), double);
            break;
         case TABLE_LDOUBLE:
            PACK(buf, table_get(t, row, col), long double);
            break;
         case TABLE_STRING:
         {
            const char *value = table_get_string(t, row, col);
            size_t size = strlen(value) + 1;
            PACK_STRING(buf, value, size);
         }
         break;
         case TABLE_CHAR:
            PACK(buf, table_get(t, row, col), char);
            break;
         case TABLE_UCHAR:
            PACK(buf, table_get(t, row, col), unsigned char);
            break;
         case TABLE_PTR:
            PACK(buf, table_get(t, row, col), void*);
            break;
         }
      }
   }
   PACK(buf, &t->callbacks_length, uint64_t);
   PACK(buf, &t->callbacks_block, uint64_t);
   for (i = 0; i < t->callbacks_length; ++i)
   {
      PACK(buf, &t->callbacks[i], table_callback_function);
      PACK(buf, &t->callbacks_data[i], void*);
      PACK(buf, &t->callbacks_registration[i], table_bitfield);
   }
}
