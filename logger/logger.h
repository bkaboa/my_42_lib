#ifndef LOGGER_H
# define LOGGER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_DEBUG
} LogLevel;

const static char *LOG_LEVELS[] = {
    "   INFO : ",
    "WARNING : ",
    "  ERROR : ",
    "  DEBUG : "
}

typedef struct {
    #ifdef FILE_LOG
        FILE *file;
    #endif
    void (*log)(const char *msg, u_int8_t log_level, ...);
} Logger;

#endif