/**
 * \file
 * \brief The table get implementation file
 * 
 * This file handles table get implementations.
 */
#include "table_defs.h"

/**
 * \brief Get a cells raw pointer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The cells raw pointer value
 */
void *table_get(const table *t, int row, int col)
{
  return table_get_cell_ptr(t, row, col)->value;
}

/**
 * \brief Get a boolean value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The boolean value
 */
bool table_get_bool(const table *t, int row, int col)
{
  return *((bool*)table_get(t, row, col));
}

/**
 * \brief Get an integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The integer value
 */
int table_get_int(const table *t, int row, int col)
{
  return *((int*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned integer value
 */
unsigned int table_get_uint(const table *t, int row, int col)
{
  return *((unsigned int*)table_get(t, row, col));
}

/**
 * \brief Get an 8-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The 8-bit integer value
 */
int8_t table_get_int8(const table *t, int row, int col)
{
  return *((int8_t*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned 8-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned 8-bit integer value
 */
uint8_t table_get_uint8(const table *t, int row, int col)
{
  return *((uint8_t*)table_get(t, row, col));
}

/**
 * \brief Get a 16-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The 16-bit integer value
 */
int16_t table_get_int16(const table *t, int row, int col)
{
  return *((int16_t*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned 16-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned 16-bit integer value
 */
uint16_t table_get_uint16(const table *t, int row, int col)
{
  return *((uint16_t*)table_get(t, row, col));
}

/**
 * \brief Get a 32-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The 32-bit integer value
 */
int32_t table_get_int32(const table *t, int row, int col)
{
  return *((int32_t*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned 32-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned 32-bit integer value
 */
uint32_t table_get_uint32(const table *t, int row, int col)
{
  return *((uint32_t*)table_get(t, row, col));
}

/**
 * \brief Get a 64-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The 64-bit integer value
 */
int64_t table_get_int64(const table *t, int row, int col)
{
  return *((int64_t*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned 64-bit integer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned 64-bit integer value
 */
uint64_t table_get_uint64(const table *t, int row, int col)
{
  return *((uint64_t*)table_get(t, row, col));
}

/**
 * \brief Get a short value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The short value
 */
short table_get_short(const table *t, int row, int col)
{
  return *((short*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned short value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned short value
 */
unsigned short table_get_ushort(const table *t, int row, int col)
{
  return *((unsigned short*)table_get(t, row, col));
}

/**
 * \brief Get a long value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The long value
 */
long table_get_long(const table *t, int row, int col)
{
  return *((long*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned long value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned long value
 */
unsigned long table_get_ulong(const table *t, int row, int col)
{
  return *((unsigned long*)table_get(t, row, col));
}

/**
 * \brief Get a long long value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The long long value
 */
long long table_get_llong(const table *t, int row, int col)
{
  return *((long long*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned long long value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned long long value
 */
unsigned long long table_get_ullong(const table *t, int row, int col)
{
  return *((unsigned long long*)table_get(t, row, col));
}

/**
 * \brief Get a float value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The float value
 */
float table_get_float(const table *t, int row, int col)
{
  return *((float*)table_get(t, row, col));
}

/**
 * \brief Get a double value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The double value
 */
double table_get_double(const table *t, int row, int col)
{
  return *((double*)table_get(t, row, col));
}

/**
 * \brief Get a long double value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The long double value
 */
long double table_get_ldouble(const table *t, int row, int col)
{
  return *((long double*)table_get(t, row, col));
}

/**
 * \brief Get a char value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The char value
 */
char table_get_char(const table *t, int row, int col)
{
  return *((char*)table_get(t, row, col));
}

/**
 * \brief Get an unsigned char value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The unsigned char value
 */
unsigned char table_get_uchar(const table *t, int row, int col)
{
  return *((unsigned char*)table_get(t, row, col));
}

/**
 * \brief Get a string value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The string value
 */
const char* table_get_string(const table *t, int row, int col)
{
  return (const char*)table_get(t, row, col);
}

/**
 * \brief Get a pointer value from the table
 * \param[in] t The table to be acted on
 * \param[in] row The table row
 * \param[in] col The table column
 * \return The pointer value
 */
void* table_get_ptr(const table *t, int row, int col)
{
  return table_get(t, row, col);
}
