include_directories(${TABLE_INCLUDE_DIR})

set(TABLE_HEADERS ${TABLE_INCLUDE_DIR}/table.h
                  ${CMAKE_CURRENT_SOURCE_DIR}/table_defs.h)

set(TABLE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/table.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_callback.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_cell.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_column.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_compare.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_find.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_get.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_row.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_set.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_sort.c
		  ${CMAKE_CURRENT_SOURCE_DIR}/table_validator.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/table_serialize.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/table_deserialize.c)
		
add_library(table ${TABLE_SOURCES} ${TABLE_HEADERS})
install(TARGETS table DESTINATION lib)
