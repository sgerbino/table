#ifndef TABLE_H_
#define TABLE_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * \brief Table position
 */
typedef enum table_position
{
  TABLE_FIRST,
  TABLE_LAST
} table_position;

/**
 * \brief Table order
 */
typedef enum table_order
{
  TABLE_ASCENDING
 ,TABLE_DESCENDING
} table_order;

/**
 * \brief Table data types
 */
typedef enum table_data_type
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
typedef enum table_event_type
{
  TABLE_DATA_MODIFIED  = 1 << 0
 ,TABLE_ROW_ADDED      = 1 << 1
 ,TABLE_ROW_REMOVED    = 1 << 2
 ,TABLE_COLUMN_ADDED   = 1 << 3
 ,TABLE_COLUMN_REMOVED = 1 << 4
 ,TABLE_SORTED         = 1 << 5
 ,TABLE_DESTROYED      = 1 << 6
} table_event_type;

/**
 * \brief A table cell comparison function
 */
typedef int (*table_comparator)(const void *value1, const void *value2);

/**
 * \brief A structure to represent table columns
 */
typedef struct table_column
{
  char *name;    /**< The name of the column */
  table_data_type type; /**< The column data type */
  table_comparator compare; /**< The column compare function */
} table_column;

/**
 * \brief A structure to represent table cells
 */
typedef struct table_cell
{
  void *value; /**< The value of the table cell */
} table_cell;

/**
 * \brief A structure to represent table rows
 */
typedef struct table_row
{
  table_cell *cells; /**< A pointer to an array of table cells */
} table_row;

/* Forward declaration */
typedef struct table table;

/**
 * \brief A table callback, handles table event notifications
 */
typedef void (*table_callback)(table *t, int row, int column, table_event_type event_type, void *data);

/**
 * \brief A table bitfield
 */
typedef unsigned int table_bitfield;

/**
 * \brief A structure to represent a table
 */
struct table
{
  /* Columns */
  table_column *columns; /**< A pointer to an array of table columns */
  int column_length; /**< The length of the array of table columns */
  size_t column_block; /**< The column block size */
  size_t columns_allocated; /**< The number of columns allocated */

  /* Rows */
  table_row *rows; /**< A pointer to an array of table rows */
  int rows_length; /**< The length of the array of table rows */
  size_t row_block; /**< The row block size */
  size_t rows_allocated; /**< The number of rows allocated */

  /* Callbacks */
  int callbacks_length; /**< The length of the array of table callbacks */
  table_callback *callbacks; /**< A pointer to an array of callbacks */
  void **callbacks_data; /**< A pointer to an array of callback data */
  table_bitfield *callbacks_registration; /**< The registration bits */
  size_t callbacks_block; /**< The callback block size */
  size_t callbacks_allocated; /**< The number of callbacks allocated */
};

static const int TABLE_INDEX_NOT_FOUND = -1;

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
int table_set(table *t, int row, int col, void* value, table_data_type data_type);
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

void *table_get(const table *t, int row, int col);
bool table_get_bool(const table *t, int row, int col);
int table_get_int(const table *t, int row, int col);
unsigned int table_get_uint(const table *t, int row, int col);
int8_t table_get_int8(const table *t, int row, int col);
uint8_t table_get_uint8(const table *t, int row, int col);
int16_t table_get_int16(const table *t, int row, int col);
uint16_t table_get_uint16(const table *t, int row, int col);
int32_t table_get_int32(const table *t, int row, int col);
uint32_t table_get_uint32(const table *t, int row, int col);
int64_t table_get_int64(const table *t, int row, int col);
uint64_t table_get_uint64(const table *t, int row, int col);
short table_get_short(const table *t, int row, int col);
unsigned short table_get_ushort(const table *t, int row, int col);
long table_get_long(const table *t, int row, int col);
unsigned long table_get_ulong(const table *t, int row, int col);
long long table_get_llong(const table *t, int row, int col);
unsigned long long table_get_ullong(const table *t, int row, int col);
float table_get_float(const table *t, int row, int col);
double table_get_double(const table *t, int row, int col);
long double table_get_ldouble(const table *t, int row, int col);
char table_get_char(const table *t, int row, int col);
unsigned char table_get_uchar(const table *t, int row, int col);
const char *table_get_string(const table *t, int row, int col);
void *table_get_ptr(const table *t, int row, int col);

/* Search functions */
int table_find(const table *t, int column_index, void* value, table_order order);
int table_find_bool(const table *t, int column_index, bool value, table_order order);
int table_find_int(const table *t, int column_index, int value, table_order order);
int table_find_uint(const table *t, int column_index, unsigned int value, table_order order);
int table_find_int8(const table *t, int column_index, int8_t value, table_order order);
int table_find_uint8(const table *t, int column_index, uint8_t value, table_order order);
int table_find_int16(const table *t, int column_index, int16_t value, table_order order);
int table_find_uint16(const table *t, int column_index, uint16_t value, table_order order);
int table_find_int32(const table *t, int column_index, int32_t value, table_order order);
int table_find_uint32(const table *t, int column_index, uint32_t value, table_order order);
int table_find_int64(const table *t, int column_index, int64_t value, table_order order);
int table_find_uint64(const table *t, int column_index, uint64_t value, table_order order);
int table_find_short(const table *t, int column_index, short value, table_order order);
int table_find_ushort(const table *t, int column_index, unsigned short value, table_order order);
int table_find_long(const table *t, int column_index, long value, table_order order);
int table_find_ulong(const table *t, int column_index, unsigned long value, table_order order);
int table_find_llong(const table *t, int column_index, long long value, table_order order);
int table_find_ullong(const table *t, int column_index, unsigned long long value, table_order order);
int table_find_float(const table *t, int column_index, float value, table_order order);
int table_find_double(const table *t, int column_index, double value, table_order order);
int table_find_ldouble(const table *t, int column_index, long double value, table_order order);
int table_find_char(const table *t, int column_index, char value, table_order order);
int table_find_uchar(const table *t, int column_index, unsigned char value, table_order order);
int table_find_string(const table *t, int column_index, const char *value, table_order order);
int table_find_ptr(const table *t, int column_index, void *value, table_order order);

int table_subset_find(const table *t, int column_index, void* value, table_order order, int minimum_index, int maximum_index);

/* Binary search functions */
int table_sorted_find(const table *t, int col, void *value, table_position position);
int table_sorted_find_int(const table *t, int col, int value, table_position position);
int table_sorted_find_uint(const table *t, int col, unsigned int value, table_position position);
int table_sorted_find_int8(const table *t, int col, int8_t value, table_position position);
int table_sorted_find_uint8(const table *t, int col, uint8_t value, table_position position);
int table_sorted_find_int16(const table *t, int col, int16_t value, table_position position);
int table_sorted_find_uint16(const table *t, int col, uint16_t value, table_position position);
int table_sorted_find_int32(const table *t, int col, int32_t value, table_position position);
int table_sorted_find_uint32(const table *t, int col, uint32_t value, table_position position);
int table_sorted_find_int64(const table *t, int col, int64_t value, table_position position);
int table_sorted_find_uint64(const table *t, int col, uint64_t value, table_position position);
int table_sorted_find_short(const table *t, int col, short value, table_position position);
int table_sorted_find_ushort(const table *t, int col, unsigned short value, table_position position);
int table_sorted_find_long(const table *t, int col, long value, table_position position);
int table_sorted_find_ulong(const table *t, int col, unsigned long value, table_position position);
int table_sorted_find_llong(const table *t, int col, long long value, table_position position);
int table_sorted_find_ullong(const table *t, int col, unsigned long long value, table_position position);
int table_sorted_find_float(const table *t, int col, float value, table_position position);
int table_sorted_find_double(const table *t, int col, double value, table_position position);
int table_sorted_find_ldouble(const table *t, int col, long double value, table_position position);
int table_sorted_find_char(const table *t, int col, char value, table_position position);
int table_sorted_find_uchar(const table *t, int col, unsigned char value, table_position position);
int table_sorted_find_string(const table *t, int col, const char *value, table_position position);
int table_sorted_find_ptr(const table *t, int col, void *value, table_position position);

/* Binary search within a row subset */
int table_sorted_subset_find(const table *t, int col, void *value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_int(const table *t, int col, int value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_uint(const table *t, int col, unsigned int value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_int8(const table *t, int col, int8_t value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_uint8(const table *t, int col, uint8_t value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_int16(const table *t, int col, int16_t value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_uint16(const table *t, int col, uint16_t value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_int32(const table *t, int col, int32_t value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_uint32(const table *t, int col, uint32_t value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_int64(const table *t, int col, int64_t value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_uint64(const table *t, int col, uint64_t value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_short(const table *t, int col, short value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_ushort(const table *t, int col, unsigned short value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_long(const table *t, int col, long value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_ulong(const table *t, int col, unsigned long value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_llong(const table *t, int col, long long value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_ullong(const table *t, int col, unsigned long long value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_float(const table *t, int col, float value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_double(const table *t, int col, double value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_ldouble(const table *t, int col, long double value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_char(const table *t, int col, char value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_uchar(const table *t, int col, unsigned char value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_string(const table *t, int col, const char *value, table_position position, int minimum, int maximum);
int table_sorted_subset_find_ptr(const table *t, int col, void *value, table_position position, int minimum, int maximum);

/* Row and column observers */
int table_get_column_length(const table *t);
int table_get_row_length(const table *t);
int table_get_callback_length(const table *t);

/* Column utilities */
table_data_type table_get_column_data_type(const table *t, int col);
int table_get_column(const table *t, const char *name);
const char *table_get_column_name(const table *t, int col);
int table_cell_nullify(table *t, int row, int col);
table_comparator table_get_column_comparator(const table *t, int column);
void table_set_column_comparator(table *t, int column, table_comparator function);

/* Sort */
void table_column_sort(table *t, int *cols, table_order *sort_orders, int num_cols);

/* Validators */
int table_column_is_valid(const table *t, int col);
int table_row_is_valid(const table *t, int row);
int table_cell_is_valid(const table *t, int row, int col);
int table_cell_has_value(const table *t, int row, int col);

/* Register callbacks */
void table_register_callback(table *t, table_callback func, void *data, table_bitfield event_types);
void table_unregister_callback(table *t, table_callback func, void *data);

/* Buffer utilities */
int table_cell_to_buffer(const table *t, int row, int col, char *buf, size_t size);
int table_cell_from_buffer(table *t, int row, int col, const char *buf);

table_comparator table_get_default_comparator_for_data_type(table_data_type type);

/* Versioning */
unsigned int table_get_major_version(void);
unsigned int table_get_minor_version(void);
unsigned int table_get_patch_version(void);
const char *table_get_version(void);

#endif /* TABLE_H_ */

