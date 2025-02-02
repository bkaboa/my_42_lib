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
    char *short_opt;
    char *long_opt;
    char *description;
    u_int8_t type;
    size_t arr_elem_size;
    bool active;
    void *value;
    void *next;
    void *prev;
}   t_opt;


int ft_set_main_opt(t_opt **opt, const enum opt_types type, const char *description);
int ft_add_new_opt(const char *short_opt, const char *long_opt, const enum opt_types type, const char *description, t_opt *opt);

int ft_getopt(const char **args, const int argc, t_opt *opt);

void print_help(t_opt *opt);

#endif