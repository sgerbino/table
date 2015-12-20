#include <table.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
   table t1, *t2;
   int random_number;
   int t1_num_cols, t2_num_cols;
   int t1_num_rows, t2_num_rows;
   int int_col, string_col;
   int row, col;
   time_t now;
   srand((unsigned int)time(&now));
   char byte_array[100000];
   const int range = 100;
   const int minimum = 100;
   int rc = 0;

   random_number = rand() % range + minimum;

   table_init(&t1);

   int_col = table_add_column(&t1, "id", TABLE_INT);
   string_col = table_add_column(&t1, "value", TABLE_STRING);

   for (row = 0; row < random_number; ++row)
   {
      char buffer[255];
      snprintf(buffer, sizeof buffer, "%d", row);

      table_add_row(&t1);
      table_set_int(&t1, row, int_col, row);
      table_set_string(&t1, row, string_col, buffer);
   }

   table_serialize(&t1, byte_array, 100000);

   t2 = table_deserialize(byte_array, 100000);

   t1_num_rows = table_get_row_length(&t1);
   t2_num_rows = table_get_row_length(t2);

   if (t2_num_rows != t1_num_rows)
   {
      printf("Failed to retrieve row length, expected %d but received %d", t1_num_rows, t2_num_rows);
      rc = -1;
   }

   t1_num_cols = table_get_column_length(&t1);
   t2_num_cols = table_get_column_length(t2);
   if (t2_num_cols != t1_num_cols)
   {
      printf("Failed to retrieve column length, expected %d but received %d", t1_num_cols, t2_num_cols);
      rc = -1;
   }

   if (t1_num_cols == t2_num_cols && t1_num_rows == t2_num_rows)
   {
      for (row = 0; row < t2_num_rows; ++row)
      {
         for (col = 0; col < t2_num_cols; ++col)
         {
            bool mismatch = false;
            table_data_type type = table_get_column_data_type(&t1, col);
            switch(type)
            {
            case TABLE_BOOL:
               mismatch = table_get_bool(&t1, row, col) != table_get_bool(t2, row, col);
               break;
            case TABLE_INT:
               mismatch = table_get_int(&t1, row, col) != table_get_int(t2, row, col);
               break;
            case TABLE_UINT:
               mismatch = table_get_uint(&t1, row, col) != table_get_uint(t2, row, col);
               break;
            case TABLE_INT8:
               mismatch = table_get_int8(&t1, row, col) != table_get_int8(t2, row, col);
               break;
            case TABLE_UINT8:
               mismatch = table_get_uint8(&t1, row, col) != table_get_uint8(t2, row, col);
               break;
            case TABLE_INT16:
               mismatch = table_get_int16(&t1, row, col) != table_get_int16(t2, row, col);
               break;
            case TABLE_UINT16:
               mismatch = table_get_uint16(&t1, row, col) != table_get_uint16(t2, row, col);
               break;
            case TABLE_INT32:
               mismatch = table_get_int32(&t1, row, col) != table_get_int32(t2, row, col);
               break;
            case TABLE_UINT32:
               mismatch = table_get_uint32(&t1, row, col) != table_get_uint32(t2, row, col);
               break;
            case TABLE_INT64:
               mismatch = table_get_int64(&t1, row, col) != table_get_int64(t2, row, col);
               break;
            case TABLE_UINT64:
               mismatch = table_get_uint64(&t1, row, col) != table_get_uint64(t2, row, col);
               break;
            case TABLE_SHORT:
               mismatch = table_get_short(&t1, row, col) != table_get_short(t2, row, col);
               break;
            case TABLE_USHORT:
               mismatch = table_get_ushort(&t1, row, col) != table_get_ushort(t2, row, col);
               break;
            case TABLE_LONG:
               mismatch = table_get_long(&t1, row, col) != table_get_long(t2, row, col);
               break;
            case TABLE_ULONG:
               mismatch = table_get_ulong(&t1, row, col) != table_get_ulong(t2, row, col);
               break;
            case TABLE_LLONG:
               mismatch = table_get_llong(&t1, row, col) != table_get_llong(t2, row, col);
               break;
            case TABLE_ULLONG:
               mismatch = table_get_ullong(&t1, row, col) != table_get_ullong(t2, row, col);
               break;
            case TABLE_FLOAT:
               mismatch = table_get_float(&t1, row, col) != table_get_float(t2, row, col);
               break;
            case TABLE_DOUBLE:
               mismatch = table_get_double(&t1, row, col) != table_get_double(t2, row, col);
               break;
            case TABLE_LDOUBLE:
               mismatch = table_get_ldouble(&t1, row, col) != table_get_ldouble(t2, row, col);
               break;
            case TABLE_STRING:
               mismatch = strcmp(table_get_string(&t1, row, col), table_get_string(t2, row, col)) != 0;
               break;
            case TABLE_CHAR:
               mismatch = table_get_char(&t1, row, col) != table_get_char(t2, row, col);
               break;
            case TABLE_UCHAR:
               mismatch = table_get_uchar(&t1, row, col) != table_get_uchar(t2, row, col);
               break;
            case TABLE_PTR:
               mismatch = table_get_ptr(&t1, row, col) != table_get_ptr(t2, row, col);
               break;
            }
            
            if (mismatch)
            {
               printf("Failed to receive correct value from cell (%d, %d)\n", row, col);
               rc = -1;
               break;
            }
         }
      }
   }

   table_destroy(&t1);
   table_delete(t2);

   return rc;
}
