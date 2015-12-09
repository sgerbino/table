/**
 * \file
 * \brief The table callback implementation file
 * 
 * This file handles table callback implementations.
 */
#include "table_defs.h"

static void table_callback_init(table *t, int callback_index, table_callback_function func, void *data, table_bitfield event_types);
static int table_get_callback_index(table *t, table_callback_function func, void *data);
static void table_add_callback_block(table *t);
static void table_remove_callback_block(table *t);

/**
 * \brief Initialize a callback
 * \param[out] t The table
 * \param[in] callback_index The callback index
 * \param[in] func The callback function
 * \param[in] data The callback data
 * \param[in] registration The callback registration
 */
static void table_callback_init(table *t, int callback_index, table_callback_function func, void *data, table_bitfield event_types)
{
  *(t->callbacks + callback_index) = func;
  *(t->callbacks_data + callback_index) = data;
  *(t->callbacks_registration + callback_index) = event_types;
}

/**
 * \brief Get the number of callbacks in the table
 * \param[in] t The table to examine
 * \return The number of callbacks
 */
int table_get_callback_length(table *t)
{
  return t->callbacks_length;
}

/**
 * \brief Register a data callback for the table
 */
void table_register_callback(table *t, table_callback_function func, void* data, table_bitfield event_types)
{
  int callback_index = table_get_callback_index(t, func, data);
  if (callback_index > 0)
  {
    t->callbacks_registration[callback_index] |= event_types;
    return;
  }

  if(!(t->callbacks_length % t->callbacks_block))
    table_add_callback_block(t);
  
  table_callback_init(t, table_get_callback_length(t), func, data, event_types);
  t->callbacks_length++;
}

/**
 * \brief Unregister a data callback for the table
 */
void table_unregister_callback(table *t, table_callback_function func, void* data)
{
  int i;
  int callback_index = table_get_callback_index(t, func, data);

  /* If a match was found, shift all the cells down */
  if(callback_index != -1)
  {
    for(i = callback_index; i < t->callbacks_length - 1; i++)
    {
      t->callbacks[i] = t->callbacks[i + 1];
      t->callbacks_data[i] = t->callbacks_data[i + 1];
      t->callbacks_registration[i] = t->callbacks_registration[i + 1];
    }

    if(!(--t->callbacks_length % t->callbacks_block))
      table_remove_callback_block(t);
  }
}

/**
 * \brief Notify registered callbacks
 * \param[in] t The table to do notifications on
 * \param[in] row_index The row number
 * \param[in] column_index The column number
 * \param[in] event_type The callback type
 */
void table_notify(table *t, int row_index, int column_index, table_event_type event_type)
{
  for (int callback_index = 0; callback_index < t->callbacks_length; callback_index++)
    if (t->callbacks_registration[callback_index] & event_type)
      t->callbacks[callback_index](t, row_index, column_index, event_type, t->callbacks_data[callback_index]);
}

/**
 * \brief Removes a callback block
 * \param[in] t The table
 */
static void table_remove_callback_block(table *t)
{
  t->callbacks_allocated -= t->callbacks_block;
  if (t->callbacks_allocated)
  {
    t->callbacks = realloc(t->callbacks, sizeof(table_callback_function) * t->callbacks_allocated);
    t->callbacks_data = realloc(t->callbacks_data, sizeof(void*) * t->callbacks_allocated);
    t->callbacks_registration = realloc(t->callbacks_registration, sizeof(table_bitfield) * t->callbacks_allocated);
  }
  else
  {
    free(t->callbacks);
    free(t->callbacks_data);
    free(t->callbacks_registration);
    t->callbacks = NULL;
    t->callbacks_data = NULL;
    t->callbacks_registration = NULL;
  }
}

/**
 * \brief Adds an additional callback block
 * \param[in] t The table
 */
static void table_add_callback_block(table *t)
{
  t->callbacks_allocated += t->callbacks_block;
  t->callbacks = realloc(t->callbacks, sizeof(table_callback_function) * t->callbacks_allocated);
  t->callbacks_data = realloc(t->callbacks_data, sizeof(void*) * t->callbacks_allocated);
  t->callbacks_registration = realloc(t->callbacks_registration, sizeof(table_bitfield) * t->callbacks_allocated);
}

/**
 * \brief Get the index of a callback
 * \param[in] t The table
 * \param[in] func The table callback function
 * \param[in] data The table callback data
 * \return The callback index
 */
static int table_get_callback_index(table *t, table_callback_function func, void *data)
{
  for(int callback_index = 0; callback_index < t->callbacks_length; callback_index++)
    if(t->callbacks[callback_index] == func && t->callbacks_data[callback_index] == data)
      return callback_index;
  return -1;
}