#include <table.h>
#include <stdio.h>

static void table_callback(table *t, int row, int col, table_event_type event_type, void *data)
{
   *(table_bitfield*)data |= event_type;
}

int main(int argc, char **argv)
{
   table t;
   table_bitfield result = 0;
   int rc = 0;
   int row;
   int col;
   
   table_init(&t);
   table_register_callback(&t, table_callback, &result, ~0);
   
   row = table_add_row(&t);
   if (!(result & TABLE_ROW_ADDED))
   {
      printf("Failed to receive TABLE_ROW_ADDED event\n");
      rc = -1;
   }

   col = table_add_column(&t, "id", TABLE_INT);
   if (!(result & TABLE_COLUMN_ADDED))
   {
      printf("Failed to receive TABLE_COLUMN_ADDED event\n");
      rc = -1;
   }

   table_set_int(&t, row, col, 42);
   if (!(result & TABLE_DATA_MODIFIED))
   {
      printf("Failed to receive TABLE_DATA_MODIFIED event");
      rc = -1;
   }

   table_remove_row(&t, row);
   if (!(result & TABLE_ROW_REMOVED))
   {
      printf("Failed to receive TABLE_ROW_REMOVED event");
      rc = -1;
   }

   table_remove_column(&t, col);
   if (!(result & TABLE_COLUMN_REMOVED))
   {
      printf("Failed to receive TABLE_COLUMN_REMOVED event");
      rc = -1;
   }

   table_destroy(&t);
   if (!(result & TABLE_DESTROYED))
   {
      printf("Failed to receive TABLE_DESTROYED event");
      rc = -1;
   }
   
   return rc;
}
