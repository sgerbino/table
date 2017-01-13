#ifndef TABLE_DEFS_H_
#define TABLE_DEFS_H_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <table.h>
#include <version.h>

/* Print formatters */
#define TABLE_CHARF    "%c"
#define TABLE_UCHARF   "%c"
#define TABLE_STRINGF  "%s"
#define TABLE_PTRF     "%p"
#define TABLE_SHORTF   "%hd"
#define TABLE_USHORTF  "%hu"
#define TABLE_INTF     "%d"
#define TABLE_UINTF    "%u"
#define TABLE_INT8F    "%"PRId8
#define TABLE_UINT8F   "%"PRIu8
#define TABLE_INT16F   "%"PRId16
#define TABLE_UINT16F  "%"PRIu16
#define TABLE_INT32F   "%"PRId32
#define TABLE_UINT32F  "%"PRIu32
#define TABLE_INT64F   "%"PRId64
#define TABLE_UINT64F  "%"PRIu64
#define TABLE_FLOATF   "%g"
#define TABLE_DOUBLEF  "%lf"
#define TABLE_LDOUBLEF "%Lg"
#define TABLE_LONGF    "%ld"
#define TABLE_ULONGF   "%lu"
#define TABLE_LLONGF   "%lld"
#define TABLE_ULLONGF  "%llu"
#define TABLE_BOOLF    TABLE_INTF

/* Scan formatters */
#define TABLE_CHARSF    TABLE_CHARF
#define TABLE_UCHARSF   TABLE_UCHARF
#define TABLE_STRINGSF  TABLE_STRINGF
#define TABLE_PTRSF     TABLE_PTRF
#define TABLE_SHORTSF   TABLE_SHORTF
#define TABLE_USHORTSF  TABLE_USHORTF
#define TABLE_INTSF     TABLE_INTF
#define TABLE_UINTSF    TABLE_UINTF
#define TABLE_INT8SF    "%"SCNd8
#define TABLE_UINT8SF   "%"SCNu8
#define TABLE_INT16SF   "%"SCNd16
#define TABLE_UINT16SF  "%"SCNu16
#define TABLE_INT32SF   "%"SCNd32
#define TABLE_UINT32SF  "%"SCNu32
#define TABLE_INT64SF   "%"SCNd64
#define TABLE_UINT64SF  "%"SCNu64
#define TABLE_FLOATSF   TABLE_FLOATF
#define TABLE_DOUBLESF  TABLE_DOUBLEF
#define TABLE_LDOUBLESF TABLE_LDOUBLEF
#define TABLE_LONGSF    TABLE_LONGF
#define TABLE_ULONGSF   TABLE_ULONGF
#define TABLE_LLONGSF   TABLE_LLONGF
#define TABLE_ULLONGSF  TABLE_ULLONGF
#define TABLE_BOOLSF    TABLE_BOOLF

/* Internal constructors */
void table_row_init(table *t, int row_index);
void table_column_init(table *t, int column_index, const char *name, table_data_type type, table_comparator func);
void table_cell_init(table *t, int row_index, int column_index);

/* Internal destructors */
void table_row_destroy(table *t, int row_index);
void table_column_destroy(table *t, int column_index);
void table_cell_destroy(table* t, int row_index, int column_index);

/* Internal event notifier */
void table_notify(table* t, int row_index, int column_index, table_event_type event_type);

/* Internal structure getters/setters */
table_cell *table_get_cell_ptr(const table *t, int row_index, int column_index);
table_column *table_get_col_ptr(const table *t, int col_num);
table_row *table_get_row_ptr(const table *t, int row_num);
void table_set_row_ptr(table *t, int row, table_row *row_ptr);

#endif
