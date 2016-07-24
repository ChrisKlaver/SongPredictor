cmake_minimum_required(VERSION 2.8.0)

project(sqlite)

add_library(sqlite
	sqlite/shell.c
	sqlite/sqlite3.c
	sqlite/sqlite3.h
	sqlite/sqlite3ext.h
  )