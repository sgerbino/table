#include "table_defs.h"

/**
 * \brief Register a data callback for the table
 */
void table_register_callback(table *t, table_callback_function func, void* data, table_bitfield event_types)
{
  table_callback_function *tmp_callback;
  void **tmp_callback_data;
  table_bitfield *tmp_callback_registration;
  size_t i;

  /* Check if this callback already exists. */
  for (i = 0; i < t->callback_len; i++)
  {
    if (t->callback[i] == func && t->callback_data[i] == data)
    {
      /* Add the new event types, if any. */
      t->callback_registration[i] |= event_types;
      return;
    }
  }

  if(!(t->callback_len % t->callback_block))
  {
    tmp_callback = calloc(t->callback_len + t->callback_block, sizeof(table_callback_function));
    tmp_callback_data = calloc(t->callback_len + t->callback_block, sizeof(void*));
    tmp_callback_registration = calloc(t->callback_len + t->callback_block, sizeof(table_bitfield*));
    if(t->callback != NULL)
    {
      memcpy(tmp_callback, t->callback, t->callback_len * sizeof(table_callback_function));
      memcpy(tmp_callback_data, t->callback_data, t->callback_len * sizeof(void*));
      memcpy(tmp_callback_registration, t->callback_registration, t->callback_len * sizeof(table_bitfield*));
      free(t->callback);
      free(t->callback_data);
      free(t->callback_registration);
    }
    t->callback = tmp_callback;
    t->callback_data = tmp_callback_data;
    t->callback_registration = tmp_callback_registration;
  }
  *(t->callback + t->callback_len) = func;
  *(t->callback_data + t->callback_len) = data;
  *(t->callback_registration + t->callback_len) = event_types;
  t->callback_len++;
}

/**
 * \brief Unregister a data callback for the table
 */
void table_unregister_callback(table *t, table_callback_function func, void* data)
{
  table_callback_function *tmp_callback;
  void **tmp_callback_data;
  table_bitfield *tmp_callback_registration;
  int i, rm = -1;

  /* Find a match */
  for(i = 0; i < t->callback_len; i++)
  {
    if(t->callback[i] == func && t->callback_data[i] == data)
    {
      rm = i;
      break;
    }
  }

  /* If a match was found, shift all the cells down */
  if(rm != -1)
  {
    for(i = rm; i < t->callback_len - 1; i++)
    {
      t->callback[i] = t->callback[i + 1];
      t->callback_data[i] = t->callback_data[i + 1];
      t->callback_registration[i] = t->callback_registration[i + 1];
    }

    if(!(--t->callback_len % t->callback_block))
    {
      if(t->callback_len != 0)
      {
        tmp_callback = calloc(t->callback_len + t->callback_block, sizeof(table_callback_function));
        tmp_callback_data = calloc(t->callback_len + t->callback_block, sizeof(void*));
        tmp_callback_registration = calloc(t->callback_len + t->callback_block, sizeof(table_bitfield*));
        memcpy(tmp_callback, t->callback, t->callback_len * sizeof(table_callback_function));
        memcpy(tmp_callback_data, t->callback_data, t->callback_len * sizeof(void*));
        memcpy(tmp_callback_registration, t->callback_registration, t->callback_len * sizeof(table_bitfield*));
        free(t->callback);
        free(t->callback_data);
        free(t->callback_registration);
        t->callback = tmp_callback;
        t->callback_data = tmp_callback_data;
        t->callback_registration = tmp_callback_registration;
      }
      else
      {
        free(t->callback);
        free(t->callback_data);
        free(t->callback_registration);
        t->callback = NULL;
        t->callback_data = NULL;
        t->callback_registration = NULL;
      }
    }
  }
}

/**
 * \brief Notify registered callbacks
 * \param[in] table The table to do notifications on
 * \param[in] row The row number
 * \param[in] col The column number
 * \param[in] cb_type The callback type
 */
void table_notify(table *t, int row, int col, table_event_type event_type)
{
  int i;
  for (i = 0; i < t->callback_len; i++)
  {
    if (t->callback_registration[i] & event_type)
    {
      t->callback[i](t, row, col, event_type, t->callback_data[i]);
    }
  }
}
