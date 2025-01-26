set(PROJECT_NAME "LIBFT")
set(VERSION 0.0.1)

set( LIBFT "ft")
set( LIBOPT "opt")

if (NOT CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    message(WARNING "actual generator " ${CMAKE_GENERATOR})
    message(FATAL_ERROR "This project only supports Makefile generator.")
endif()