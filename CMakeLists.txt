cmake_minimum_required(VERSION 2.8)
project(TABLE C)

set(TABLE_MAINTAINER "Steve Gerbino <steve@gerbino.co>")
set(TABLE_DESCRIPTION "A C implementation of a relational table with useful features such as sorting, searching, and callback mechanisms.")

set(TABLE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TABLE_GENERATED_INCLUDE_DIR ${CMAKE_BINARY_DIR}/include)
set(TABLE_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(TABLE_CONF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/conf)
set(CMAKE_MODULE_PATH ${TABLE_CMAKE_DIR})

include_directories(${TABLE_INCLUDE_DIR})
include_directories(${TABLE_GENERATED_INCLUDE_DIR})

include(platform)
include(versioning)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

include(documentation)
include(packaging)
