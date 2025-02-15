#ifndef OPTLIB_H
# define OPTLIB_H

#include "../libft/libft.h"
#include <stdio.h>

#define OPT_ERROR 1
#define OPT_SUCCESS 0

enum opt_types {
    OPT_NONE = 0x0,
    OPT_STRING = 0x1,
    OPT_LONG = 0x2,
    OPT_ARRAY = 0x4,
};

typedef struct {
    char short_opt;
    char *long_opt;
    char *description;
    u_int8_t type;
    size_t arr_elem_size;
    size_t option;
    bool active;
    void *value;
    void *next;
    void *prev;
}   t_opt;


int opt_set_main(t_opt **opt, const enum opt_types type, const char *description);
void opt_destroy(t_opt **opt);
int opt_add_new(const char short_opt, const char *long_opt, const enum opt_types type, const char *description, size_t option, t_opt *opt);
void opt_print_help(const t_opt *opt);

void debug_opt(t_opt *opt);

int ft_getopt(const char **args, const int argc, t_opt *opt);

#endif