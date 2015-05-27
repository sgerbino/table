#ifndef TABLE_H_
#define TABLE_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * \brief Table order
 */
typedef enum _table_order
{
  TABLE_ASCENDING
 ,TABLE_DESCENDING
} table_order;

/**
 * \brief Table data types
 */
typedef enum _table_data_type
{
  TABLE_INT
 ,TABLE_UINT
 ,TABLE_INT8
 ,TABLE_UINT8
 ,TABLE_INT16
 ,TABLE_UINT16
 ,TABLE_INT32
 ,TABLE_UINT32
 ,TABLE_INT64
 ,TABLE_UINT64
 ,TABLE_SHORT
 ,TABLE_USHORT
 ,TABLE_LONG
 ,TABLE_ULONG
 ,TABLE_LLONG
 ,TABLE_ULLONG
 ,TABLE_FLOAT
 ,TABLE_DOUBLE
 ,TABLE_LDOUBLE
 ,TABLE_CHAR
 ,TABLE_UCHAR
 ,TABLE_STRING
 ,TABLE_BOOL
 ,TABLE_PTR
} table_data_type;

/**
 * \brief Table event types
 */
typedef enum _table_event_type
{
  TABLE_DATA_MODIFIED  = 1 << 0
 ,TABLE_ROW_ADDED      = 1 << 1
 ,TABLE_ROW_REMOVED    = 1 << 2
 ,TABLE_COLUMN_ADDED   = 1 << 3
 ,TABLE_COLUMN_REMOVED = 1 << 4
} table_event_type;

/**
 * \brief A structure to represent table columns
 */
typedef struct _table_column
{
  char *name;    /**< The name of the column */
  table_data_type type; /**< The column data type */
} table_column;

/**
 * \brief A structure to represent table cells
 */
typedef struct _table_cell
{
  void *value; /**< The value of the table cell */
} table_cell;

/**
 * \brief A structure to represent table rows
 */
typedef struct _table_row
{
  table_cell *cells;    /**< A pointer to an array of table cells */
} table_row;

/* Forward declaration */
typedef struct _table table;

/**
 * \brief A table callback, handles table event notifications
 */
typedef void (*table_callback_function)(table *t, int row, int col, table_event_type event_type, void *data);

/**
 * \brief A table bitfield
 */
typedef unsigned int table_bitfield;

/**
 * \brief A structure to represent a table
 */
typedef struct _table
{
  /* Columns */
  table_column *cols; /**< A pointer to an array of table columns */
  uint64_t cols_len;    /**< The length of the array of table columns */
  uint64_t col_block; /**< The column block size */
  size_t cols_allocated; /**< The number of columns allocated */

  /* Rows */
  table_row *rows; /**< A pointer to an array of table rows */
  uint64_t rows_len;    /**< The length of the array of table rows */
  uint64_t row_block; /**< The row block size */
  size_t rows_allocated; /**< The number of rows allocated */

  /* Callbacks */
  uint64_t callback_len; /**< The length of the array of table callbacks */
  table_callback_function *callback; /**< A pointer to an array of callbacks */
  void **callback_data; /**< A pointer to an array of callback data */
  table_bitfield *callback_registration; /**< The registration bits */
  uint64_t callback_block; /**< The callback block size */
  size_t callbacks_allocated; /**< The number of callbacks allocated */
} table;

/* Memory allocation, deallocation, and manipulation */
table *table_new(void);
void table_delete(void *t);
void table_init(table *t);
void table_destroy(table *t);
table *table_dupe(table *t);

/* Row and column manipulation */
int table_add_column(table *t, const char *name, table_data_type data_type);
int table_remove_column(table *t, int col);
int table_add_row(table *t);
int table_remove_row(table *t, int row);

/* Cell value manipulation */
int table_set(table *t, int row, int col, void *value, table_data_type data_type);
int table_set_bool(table *t, int row, int col, bool value);
int table_set_int(table *t, int row, int col, int value);
int table_set_uint(table *t, int row, int col, unsigned int value);
int table_set_int8(table *t, int row, int col, int8_t value);
int table_set_uint8(table *t, int row, int col, uint8_t value);
int table_set_int16(table *t, int row, int col, int16_t value);
int table_set_uint16(table *t, int row, int col, uint16_t value);
int table_set_int32(table *t, int row, int col, int32_t value);
int table_set_uint32(table *t, int row, int col, uint32_t value);
int table_set_int64(table *t, int row, int col, int64_t value);
int table_set_uint64(table *t, int row, int col, uint64_t value);
int table_set_short(table *t, int row, int col, short value);
int table_set_ushort(table *t, int row, int col, unsigned short value);
int table_set_long(table *t, int row, int col, long value);
int table_set_ulong(table *t, int row, int col, unsigned long value);
int table_set_llong(table *t, int row, int col, long long value);
int table_set_ullong(table *t, int row, int col, unsigned long long value);
int table_set_float(table *t, int row, int col, float value);
int table_set_double(table *t, int row, int col, double value);
int table_set_ldouble(table *t, int row, int col, long double value);
int table_set_char(table *t, int row, int col, char value);
int table_set_uchar(table *t, int row, int col, unsigned char value);
int table_set_string(table *t, int row, int col, const char *value);
int table_set_ptr(table *t, int row, int col, void *value);

void *table_get(table *t, int row, int col);
bool table_get_bool(table *t, int row, int col);
int table_get_int(table *t, int row, int col);
unsigned int table_get_uint(table *t, int row, int col);
int8_t table_get_int8(table *t, int row, int col);
uint8_t table_get_uint8(table *t, int row, int col);
int16_t table_get_int16(table *t, int row, int col);
uint16_t table_get_uint16(table *t, int row, int col);
int32_t table_get_int32(table *t, int row, int col);
uint32_t table_get_uint32(table *t, int row, int col);
int64_t table_get_int64(table *t, int row, int col);
uint64_t table_get_uint64(table *t, int row, int col);
short table_get_short(table *t, int row, int col);
unsigned short table_get_ushort(table *t, int row, int col);
long table_get_long(table *t, int row, int col);
unsigned long table_get_ulong(table *t, int row, int col);
long long table_get_llong(table *t, int row, int col);
unsigned long long table_get_ullong(table *t, int row, int col);
float table_get_float(table *t, int row, int col);
double table_get_double(table *t, int row, int col);
long double table_get_ldouble(table *t, int row, int col);
char table_get_char(table *t, int row, int col);
unsigned char table_get_uchar(table *t, int row, int col);
const char *table_get_string(table *t, int row, int col);
void *table_get_ptr(table *t, int row, int col);

/* Search functions */
int table_find(table *t, int col, void *value, table_data_type data_type, table_order order);
int table_find_bool(table *t, int col, bool value, table_order order);
int table_find_int(table *t, int col, int value, table_order order);
int table_find_uint(table *t, int col, unsigned int value, table_order order);
int table_find_int8(table *t, int col, int8_t value, table_order order);
int table_find_uint8(table *t, int col, uint8_t value, table_order order);
int table_find_int16(table *t, int col, int16_t value, table_order order);
int table_find_uint16(table *t, int col, uint16_t value, table_order order);
int table_find_int32(table *t, int col, int32_t value, table_order order);
int table_find_uint32(table *t, int col, uint32_t value, table_order order);
int table_find_int64(table *t, int col, int64_t value, table_order order);
int table_find_uint64(table *t, int col, uint64_t value, table_order order);
int table_find_short(table *t, int col, short value, table_order order);
int table_find_ushort(table *t, int col, unsigned short value, table_order order);
int table_find_long(table *t, int col, long value, table_order order);
int table_find_ulong(table *t, int col, unsigned long value, table_order order);
int table_find_llong(table *t, int col, long long value, table_order order);
int table_find_ullong(table *t, int col, unsigned long long value, table_order order);
int table_find_float(table *t, int col, float value, table_order order);
int table_find_double(table *t, int col, double value, table_order order);
int table_find_ldouble(table *t, int col, long double value, table_order order);
int table_find_char(table *t, int col, char value, table_order order);
int table_find_uchar(table *t, int col, unsigned char value, table_order order);
int table_find_string(table *t, int col, const char *value, table_order order);
int table_find_ptr(table *t, int col, void *value, table_order order);

/* Row and column observers */
int table_get_column_length(table *t);
int table_get_row_length(table *t);

/* Column utilities */
table_data_type table_get_column_data_type(table *t, int col);
int table_get_column(table *t, const char *name);
const char *table_get_column_name(table *t, int col);
int table_cell_nullify(table *t, int row, int col);

/* Validators */
int table_column_is_valid(table *t, int col);
int table_row_is_valid(table *t, int row);
int table_cell_is_valid(table *t, int row, int col);
int table_cell_has_value(table *t, int row, int col);

/* Register callbacks */
void table_register_callback(table *t, table_callback_function func, void *data, table_bitfield event_types);
void table_unregister_callback(table *t, table_callback_function func, void *data);

/* Buffer utilities */
int table_cell_to_string(table *t, int row, int col, char *buf, size_t size);
int table_cell_from_string(table *t, int row, int col, const char *buf);

void table_serialize(table *t, void *buf, size_t len);
table *table_deserialize(void *buf, size_t len);

#endif /* TABLE_H_ */
