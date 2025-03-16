#ifndef OPTLIB_H
# define OPTLIB_H

#include "../libft/libft.h"
#include <stdio.h>

#define OPT_ERROR 1
#define OPT_SUCCESS 0
#define OPT_HELP 2

typedef struct {
    char short_opt;
    char *long_opt;
    char *description;
    size_t arr_elem_size;
    void *(*func)(const char *arg);
    bool argument;
    bool required;
    bool is_set;
    void *value;
    size_t nb_value_elem;
    void *next;
    void *prev;
}   t_opt;

typedef struct {
    t_opt *head;
    t_opt *tail;
    t_opt main;
}  t_opt_list;

int opt_set_main(t_opt_list *opt_list, const char description[]);
void opt_destroy(t_opt **opt);
int opt_add_new(const char short_opt, const char *long_opt, const char *description, const bool required, void *(*func)(void*), const bool argument, t_opt_list opt_list);
void opt_print_help(const t_opt *opt);

void debug_opt(t_opt *opt);

int ft_getopt(const char **args, const int argc, t_opt *opt);

#endif