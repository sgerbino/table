include_directories(${TABLE_INCLUDE_DIRS})

# The core table implementation in C.
set(TABLE_HEADERS ${TABLE_INCLUDE_DIRS}/table.h)
set(TABLE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/table.c)
add_library(table SHARED ${TABLE_SOURCES} ${TABLE_HEADERS})
