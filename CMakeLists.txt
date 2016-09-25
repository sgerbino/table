cmake_minimum_required(VERSION 2.8)
project(TABLE C)

set(TABLE_MAINTAINER "Steve Gerbino <steve@gerbino.co>")
set(TABLE_DESCRIPTION "A C implementation of a relational table with useful features such as sorting, searching, and callback mechanisms.")

set(TABLE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TABLE_GENERATED_INCLUDE_DIR ${CMAKE_BINARY_DIR}/include)
set(TABLE_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(TABLE_CONF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/conf)
set(CMAKE_MODULE_PATH ${TABLE_CMAKE_DIR})

string(TOLOWER "lib${PROJECT_NAME}" TABLE_PACKAGE_NAME)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")

include(ExternalProject)
ExternalProject_Add(
   json-c
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/json-c"
   CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
set(JSON-C_LIBRARIES ${CMAKE_BINARY_DIR}/lib/${CMAKE_SHARED_MODULE_PREFIX}json-c${CMAKE_STATIC_LIBRARY_SUFFIX})

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include/json-c)
include_directories(${TABLE_INCLUDE_DIR})
include_directories(${TABLE_GENERATED_INCLUDE_DIR})

include(CTest)
include(platform)
include(versioning)
include(arch)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

include(documentation)
include(packaging)
