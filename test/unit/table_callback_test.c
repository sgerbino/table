#include "table_test.h"

static void table_callback(table *t, int row, int col, table_event_type event_type, void *data)
{
   *(table_bitfield*)data |= event_type;
}

bool table_callback_test(char *buf, size_t len)
{
   table t;
   table_bitfield result = 0;
   bool rc = true;
   int row;
   int col;
   
   table_init(&t);
   table_register_callback(&t, table_callback, &result, ~0);
   
   row = table_add_row(&t);
   if (!(result & TABLE_ROW_ADDED))
   {
      snprintf(buf, len, "Failed to receive TABLE_ROW_ADDED event");
      rc = false;
   }

   col = table_add_column(&t, "id", TABLE_INT);
   if (!(result & TABLE_COLUMN_ADDED))
   {
      snprintf(buf, len, "Failed to receive TABLE_COLUMN_ADDED event");
      rc = false;
   }

   table_set_int(&t, row, col, 42);
   if (!(result & TABLE_DATA_MODIFIED))
   {
      snprintf(buf, len, "Failed to receive TABLE_DATA_MODIFIED event");
      rc = false;
   }

   table_remove_row(&t, row);
   if (!(result & TABLE_ROW_REMOVED))
   {
      snprintf(buf, len, "Failed to receive TABLE_ROW_REMOVED event");
      rc = false;
   }

   table_remove_column(&t, col);
   if (!(result & TABLE_COLUMN_REMOVED))
   {
      snprintf(buf, len, "Failed to receive TABLE_COLUMN_REMOVED event");
      rc = false;
   }

   table_unregister_callback(&t, table_callback, &result);
   table_destroy(&t);
   return rc;
}
