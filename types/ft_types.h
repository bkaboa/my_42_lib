#ifndef FT_TYPES_H
#define FT_TYPES_H

#include <stdint.h>
#include <sys/types.h>

enum {
    STATUS_OK = 0,
    STATUS_ERROR = 1,
    STATUS_NOT_FOUND = 2,
    STATUS_INVALID_ARGUMENT = 3,
    STATUS_OUT_OF_MEMORY = 4
} e_status;

typedef u_int8_t STATUS;

typedef char* t_string;

typedef int fd_t;

#endif