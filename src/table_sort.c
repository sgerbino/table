/**
 * \file
 * \brief The table sort implementation file
 * \author Derrick Menn
 * \author Steve Gerbino
 * 
 * This file handles table sort implementations. The table sort implementation uses a merge sort algorithm.
 * 
 * In computer science, merge sort (also commonly spelled mergesort) is an O(n log n) comparison-based sorting algorithm. 
 * Most implementations produce a stable sort, which means that the implementation preserves the input order of equal 
 * elements in the sorted output. Mergesort is a divide and conquer algorithm that was invented by John von Neumann in 
 * 1945.[1] A detailed description and analysis of bottom-up mergesort appeared in a report by Goldstine and Neumann as 
 * early as 1948.
 * 
 * \a Source: <a href="https://en.wikipedia.org/wiki/Merge_sort">\a Merge \a sort \a - \a Wikipedia, \a the \a free \a encyclopedia</a>
 */
#include "table_defs.h"

static void table_merge_sort_rows(table *t, int col, int first, int last, table_order order);
static void table_merge_sort_split_rows(table *t, table_row *sorted_rows, int col, int first, int last, table_order order);
static void table_merge_sort_merge_rows(table *t, table_row *sorted_rows, int col, int first, int middle, int last, table_order order);
static void table_merge_sort_copy_rows(table *t, int first, int last, table_row *sorted_rows);

/**
 * \brief Multi-column sort
 * \author Derrick Menn
 * \param[in] table The table to be sorted
 * \param[in] cols Array of indices of the columns to be sorted
 * \param[in] sort_orders Array of sort orders for each column
 * \param[in] num_cols Number of columns to be sorted
 * \return
 */
void table_column_sort(table *t, int *cols, table_order *sort_orders, int num_cols)
{
   int sort_column;
   for (sort_column = 0; sort_column < num_cols; sort_column++)
   {
      int num_rows = table_get_row_length(t);
      if (!sort_column)
      {
         table_merge_sort_rows(t, cols[sort_column], 0, num_rows-1, sort_orders[sort_column]);
      }
      else
      {
         int row, first = -1, last = -1;
	 table_compare_function compare = table_get_column_compare_function(t, cols[sort_column - 1]);
         for (row = 0; row < num_rows; row++)
         {
            if (row)
            {
               int prior_column;
               bool equal = false;
               for (prior_column = sort_column - 1; prior_column >= 0; prior_column--)
               {
                  equal = !compare(table_get(t, row, cols[prior_column]), table_get(t, row - 1, cols[prior_column]));
                  if (!equal)
                     break;
               }
               if (equal)
               {
                  if (first == -1)
                     first = row - 1;
                  last = row;
               }
            }
            if (first != -1 && (last != row || last == num_rows - 1))
            {
               table_merge_sort_rows(t, cols[sort_column], first, last, sort_orders[sort_column]);
               first = -1;
               last = -1;
            }
         }
      }
   }
   table_notify(t, -1, -1, TABLE_SORTED);
}

/**
 * \brief Row merge sort main function
 * \author Derrick Menn
 * \param[in] t The table to be sorted
 * \param[in] col The column to sort by
 * \param[in] first The first row to sort
 * \param[in] last The last row to sort
 * \param[in] order The table_order to sort the rows by
 */
static void table_merge_sort_rows(table *t, int col, int first, int last, table_order order)
{
   table_row *sorted_rows = calloc(last - first + 1, sizeof(table_row));
   table_merge_sort_split_rows(t, sorted_rows, col, first, last, order);
   free(sorted_rows);
}

/**
 * \brief Row merge sort split row list into row sublist function
 * \author Derrick Menn
 * \param[in] t The table to be sorted
 * \param[in] sorted_rows Array to hold the sorted rows
 * \param[in] col The column to sort the table rows by
 * \param[in] first The first row to start sorting at
 * \param[in] last The last row to sort
 * \param[in] order The table_order to sort by
 */
static void table_merge_sort_split_rows(table *t, table_row *sorted_rows, int col, int first, int last, table_order order)
{
   if (last - first + 1 < 2)
      return;
   int middle = (first + last)/2;
   table_merge_sort_split_rows(t, sorted_rows, col, first, middle, order);
   table_merge_sort_split_rows(t, sorted_rows, col, middle + 1, last, order);
   table_merge_sort_merge_rows(t, sorted_rows, col, first, middle, last, order);
   table_merge_sort_copy_rows(t, first, last, sorted_rows);
}

/**
 * \brief Row merge sort merge row sublists function
 * \author Derrick Menn
 * \param[in] t The table to sort by
 * \param[in] sorted_rows Array to hold the sorted rows
 * \param[in] col The column to sort table rows by
 * \param[in] first The index of the first row in the sublist
 * \param[in] middle The index of the middle row in the sublist
 * \param[in] last The index of the last row in the sublist
 * \param[in] order The table_order to sort by
 */
static void table_merge_sort_merge_rows(table *t, table_row *sorted_rows, int col, int first, int middle, int last, table_order order)
{
   int n1 = first, n2 = middle + 1, i;
   table_compare_function compare = table_get_column_compare_function(t, col);
   for (i = 0; i < last - first + 1; i++)
   {
      if (order == TABLE_ASCENDING)
      {
         if (n1 <= middle && (n2 > last || compare(table_get(t, n1, col), table_get(t, n2, col)) < 0))
         {
            sorted_rows[i] = *table_get_row_ptr(t, n1);
            n1++;
         }
         else
         {
            sorted_rows[i] = *table_get_row_ptr(t, n2);
            n2++;
         }
      }
      else
      {
         if (n1 <= middle && (n2 > last || compare(table_get(t, n1, col), table_get(t, n2, col)) > 0))
         {
            sorted_rows[i] = *table_get_row_ptr(t, n1);
            n1++;
         }
         else
         {
            sorted_rows[i] = *table_get_row_ptr(t, n2);
            n2++;
         }
      }
   }
}

/**
 * \brief Row merge sort copy sorted rows back into table
 * \author Derrick Menn
 * \param[in] t The table to be sorted
 * \param[in] first The index of the first row that was sorted
 * \param[in] last The index of the last row that was sorted
 * \param[in] sorted_rows Array of sorted rows
 */
static void table_merge_sort_copy_rows(table *t, int first, int last, table_row *sorted_rows)
{
   int i = 0;
   for (i = 0; i < last - first + 1; i++)
      table_set_row_ptr(t, first+i, &sorted_rows[i]);
}
