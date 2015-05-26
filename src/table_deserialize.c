#include "table_private.h"

#define UNPACK(destination, source, type)       \
   do {                                         \
      *(type*)destination = *(type*)source;     \
      source = (char*)source + sizeof (type);   \
   } while (0)

#define UNPACK_STRING(destination, source, length)                      \
   do {                                                                 \
      uint64_t len;                                                     \
      UNPACK(&len, source, uint64_t);                                   \
      strncpy(destination, source, length < len ? length : len);        \
      source = (char*)source + len;                                     \
   } while (0)

table *table_deserialize(void *buf, size_t len)
{
   uint64_t row_len;
   uint64_t col_len;
   uint64_t row, col;
   table *t = table_new();

   UNPACK(&col_len, buf, uint64_t);
   for (col = 0; col < col_len; ++col)
   {
      char name[255];
      uint64_t len;
      table_data_type type;
      UNPACK(&len, buf, uint64_t);
      UNPACK_STRING(name, buf, sizeof name);
      UNPACK(&type, buf, table_data_type);
      table_add_column(t, name, type);
   }

   UNPACK(&row_len, buf, uint64_t);
   for (row = 0; row < row_len; ++row)
   {
      table_add_row(t);
      for (col = 0; col < col_len; ++col)
      {
         table_data_type type = table_get_column_data_type(t, col);

         switch(type)
         {
         case TABLE_BOOL:
         {
            bool value;
            UNPACK(&value, buf, bool);
            table_set_bool(t, row, col, value);
         }
         break;
         case TABLE_INT:
         {
            int value;
            UNPACK(&value, buf, int);
            table_set_int(t, row, col, value);
         }
         break;
         case TABLE_UINT:
         {
            unsigned int value;
            UNPACK(&value, buf, unsigned int);
            table_set_uint(t, row, col, value);
         }
         break;
         case TABLE_INT8:
         {
            int8_t value;
            UNPACK(&value, buf, int8_t);
            table_set_int8(t, row, col, value);
         }
         break;
         case TABLE_UINT8:
         {
            uint8_t value;
            UNPACK(&value, buf, uint8_t);
            table_set_uint8(t, row, col, value);
         }
         break;
         case TABLE_INT16:
         {
            int16_t value;
            UNPACK(&value, buf, int16_t);
            table_set_int16(t, row, col, value);
         }
         break;
         case TABLE_UINT16:
         {
            uint16_t value;
            UNPACK(&value, buf, uint16_t);
            table_set_uint16(t, row, col, value);
         }
         break;
         case TABLE_INT32:
         {
            int32_t value;
            UNPACK(&value, buf, int32_t);
            table_set_int32(t, row, col, value);
         }
         break;
         case TABLE_UINT32:
         {
            uint32_t value;
            UNPACK(&value, buf, uint32_t);
            table_set_uint32(t, row, col, value);
         }
         break;
         case TABLE_INT64:
         {
            int64_t value;
            UNPACK(&value, buf, int64_t);
            table_set_int64(t, row, col, value);
         }
         break;
         case TABLE_UINT64:
         {
            uint64_t value;
            UNPACK(&value, buf, uint64_t);
            table_set_uint64(t, row, col, value);
         }
         break;
         case TABLE_SHORT:
         {
            short value;
            UNPACK(&value, buf, short);
            table_set_short(t, row, col, value);
         }
         break;
         case TABLE_USHORT:
         {
            unsigned short value;
            UNPACK(&value, buf, unsigned short);
            table_set_ushort(t, row, col, value);
         }
         break;
         case TABLE_LONG:
         {
            long value;
            UNPACK(&value, buf, long);
            table_set_long(t, row, col, value);
         }
         break;
         case TABLE_ULONG:
         {
            unsigned long value;
            UNPACK(&value, buf, unsigned long);
            table_set_ulong(t, row, col, value);
         }
         break;
         case TABLE_LLONG:
         {
            long long value;
            UNPACK(&value, buf, long long);
            table_set_llong(t, row, col, value);
         }
         break;
         case TABLE_ULLONG:
         {
            unsigned long long value;
            UNPACK(&value, buf, unsigned long long);
            table_set_ullong(t, row, col, value);
         }
         break;
         case TABLE_FLOAT:
         {
            float value;
            UNPACK(&value, buf, float);
            table_set_float(t, row, col, value);
         }
         break;
         case TABLE_DOUBLE:
         {
            double value;
            UNPACK(&value, buf, double);
            table_set_double(t, row, col, value);
         }
         break;
         case TABLE_LDOUBLE:
         {
            long double value;
            UNPACK(&value, buf, long double);
            table_set_ldouble(t, row, col, value);
         }
         break;
         case TABLE_STRING:
         {
            char string[255] = {0};
            UNPACK_STRING(string, buf, sizeof string);
            table_set_string(t, row, col, string);
         }
         break;
         case TABLE_CHAR:
         {
            char value;
            UNPACK(&value, buf, char);
            table_set_char(t, row, col, value);
         }
         break;
         case TABLE_UCHAR:
         {
            unsigned char value;
            UNPACK(&value, buf, unsigned char);
            table_set_uchar(t, row, col, value);
         }
         break;
         case TABLE_PTR:
         {
            void *value;
            UNPACK(&value, buf, void*);
            table_set_ptr(t, row, col, value);
         }
         break;
         }
      }
   }

   return t;
}
