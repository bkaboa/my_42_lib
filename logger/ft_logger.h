#ifndef LOGGER_H
# define LOGGER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
# include <stdbool.h>

#include <sys/types.h>

#include "ft_color.h"

typedef enum {
    E_LOG_INFO,
    E_LOG_WARNING,
    E_LOG_ERROR,
    E_LOG_DEBUG
} LogLevel;

# define COLOR_MSG(log_level) (log_level) == E_LOG_INFO ? COLOR_WHITE : log_level == E_LOG_WARNING ? COLOR_YELLOW : log_level == E_LOG_ERROR ? COLOR_RED : COLOR_BLUE

# define LOG_STD(log_level) (log_level) == E_LOG_ERROR ? STDERR_FILENO : STDOUT_FILENO

static const char *LOG_LEVELS_MSG[] = {
    "INFO    : ",
    "WARNING : ",
    "ERROR   : ",
    "DEBUG   : "
};

typedef struct {
    #ifdef FILE_LOG
        FILE *file;
    #endif
    void (*log)(const u_int8_t log_level, const bool prefix, const char *msg, ...);
} Logger;

Logger *get_logger_instance();

#endif