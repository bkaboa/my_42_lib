set(PROJECT_NAME "LIBFT")
set(VERSION 0.0.1)

set( LIBFT_NAME "ft")
set( LIBOPT_NAME "opt")
set( LIBLOGGER_NAME "logger")


if (NOT CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    message(WARNING "actual generator " ${CMAKE_GENERATOR})
    message(FATAL_ERROR "This project only supports Makefile generator.")
endif()