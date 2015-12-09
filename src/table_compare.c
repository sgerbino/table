/**
 * \file
 * \brief The table compare implementation file
 * 
 * This file handles table compare implementations.
 */
#include "table_defs.h"

#define TABLE_COMPARE_POINTERS(value1, value2) \
do                                             \
{                                              \
   if (value1 == NULL)                         \
      if (value2 == NULL)                      \
         return 0;                             \
      else                                     \
         return -1;                            \
   else if (value2 == NULL)                    \
      return 1;                                \
} while (0);                                   \

#define TABLE_COMPARE_VALUES(value1, value2)   \
do                                             \
{                                              \
   if (value1 > value2)                        \
      return 1;                                \
   else if (value1 < value2)                   \
      return -1;                               \
} while (0);                                   \
    

int table_compare_bool(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   bool val1 = *(bool*)value1;
   bool val2 = *(bool*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_int(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   int val1 = *(int*)value1;
   int val2 = *(int*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_uint(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   unsigned int val1 = *(unsigned int*)value1;
   unsigned int val2 = *(unsigned int*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_int8(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   int8_t val1 = *(int8_t*)value1;
   int8_t val2 = *(int8_t*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_uint8(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   uint8_t val1 = *(uint8_t*)value1;
   uint8_t val2 = *(uint8_t*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_int16(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   int16_t val1 = *(int16_t*)value1;
   int16_t val2 = *(int16_t*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_uint16(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   uint16_t val1 = *(uint16_t*)value1;
   uint16_t val2 = *(uint16_t*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_int32(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   int32_t val1 = *(int32_t*)value1;
   int32_t val2 = *(int32_t*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_uint32(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   uint32_t val1 = *(uint32_t*)value1;
   uint32_t val2 = *(uint32_t*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_int64(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   int64_t val1 = *(int64_t*)value1;
   int64_t val2 = *(int64_t*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_uint64(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   uint64_t val1 = *(uint64_t*)value1;
   uint64_t val2 = *(uint64_t*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_short(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   short val1 = *(short*)value1;
   short val2 = *(short*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_ushort(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   unsigned short val1 = *(unsigned short*)value1;
   unsigned short val2 = *(unsigned short*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_long(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   long val1 = *(long*)value1;
   long val2 = *(long*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_ulong(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   unsigned long val1 = *(unsigned long*)value1;
   unsigned long val2 = *(unsigned long*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_llong(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   long long val1 = *(long long*)value1;
   long long val2 = *(long long*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_ullong(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   unsigned long val1 = *(unsigned long*)value1;
   unsigned long val2 = *(unsigned long*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_float(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   float val1 = *(float*)value1;
   float val2 = *(float*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_double(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   double val1 = *(double*)value1;
   double val2 = *(double*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_ldouble(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   long double val1 = *(long double*)value1;
   long double val2 = *(long double*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_char(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   char val1 = *(char*)value1;
   char val2 = *(char*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_uchar(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   unsigned char val1 = *(unsigned char*)value1;
   unsigned char val2 = *(unsigned char*)value2;
   TABLE_COMPARE_VALUES(val1, val2);
   return 0;
}

int table_compare_string(void *value1, void *value2)
{
   TABLE_COMPARE_POINTERS(value1, value2);
   const char *val1 = (const char*)value1;
   const char *val2 = (const char*)value2;
   return strcmp(val1, val2);
}

int table_compare_ptr(void *value1, void *value2)
{
   if (value1 > value2)
      return 1;
   else if (value1 < value2)
      return -1;
   return 0;
}

/**
 * \brief Get the default comparison function for a given data type
 * \author Steve Gerbino
 * \param[in] type The data type
 * \return The corresponding table compare function pointer
 */
table_compare_function table_get_default_compare_function_for_data_type(table_data_type type)
{
   table_compare_function func = NULL;

   switch(type)
   {
   case TABLE_INT:
      func = table_compare_int;
      break;
   case TABLE_UINT:
      func = table_compare_uint;
      break;
   case TABLE_INT8:
      func = table_compare_int8;
      break;
   case TABLE_UINT8:
      func = table_compare_uint8;
      break;
   case TABLE_INT16:
      func = table_compare_int16;
      break;
   case TABLE_UINT16:
      func = table_compare_uint16;
      break;
   case TABLE_INT32:
      func = table_compare_int32;
      break;
   case TABLE_UINT32:
      func = table_compare_uint32;
      break;
   case TABLE_INT64:
      func = table_compare_int64;
      break;
   case TABLE_UINT64:
      func = table_compare_uint64;
      break;
   case TABLE_SHORT:
      func = table_compare_short;
      break;
   case TABLE_USHORT:
      func = table_compare_ushort;
      break;
   case TABLE_LONG:
      func = table_compare_long;
      break;
   case TABLE_ULONG:
      func = table_compare_ulong;
      break;
   case TABLE_LLONG:
      func = table_compare_llong;
      break;
   case TABLE_ULLONG:
      func = table_compare_ullong;
      break;
   case TABLE_STRING:
      func = table_compare_string;
      break;
   case TABLE_FLOAT:
      func = table_compare_float;
      break;
   case TABLE_DOUBLE:
      func = table_compare_double;
      break;
   case TABLE_LDOUBLE:
      func = table_compare_ldouble;
      break;
   case TABLE_BOOL:
      func = table_compare_bool;
      break;
   case TABLE_CHAR:
      func = table_compare_char;
      break;
   case TABLE_UCHAR:
      func = table_compare_uchar;
      break;
   case TABLE_PTR:
      func = table_compare_ptr;
      break;
   }

   return func;
}


