#ifndef OPTLIB_H
# define OPTLIB_H

#include "libft/libft.h"
#include "logger/ft_color.h"
#include <stdio.h>

#define OPT_ERROR 1
#define OPT_SUCCESS 0
#define OPT_HELP 2

typedef int (*t_opt_func)(const char *arg, void *obj);

typedef struct s_opt {
    char short_opt;
    size_t long_opt_len;
    char *long_opt;
    char *description;
    size_t arr_elem_size;
    t_opt_func func;
    bool argument;
    bool required;
    bool is_set;
    void *value;
    size_t nb_value_elem;
    struct s_opt *next;
    struct s_opt *prev;
}   t_opt;

typedef struct {
    t_opt *head;
    t_opt *tail;
    t_opt *by_short[256];
    t_opt empty_opt_arg;
    t_opt main;
}  t_opt_list;

int opt_set_main(t_opt_list *opt_list, const char description[], t_opt_func func);
int opt_empty(t_opt_list *opt_list, const char *description, t_opt_func func);
void opt_destroy(t_opt_list *opt_lists);
int opt_add_new(const char short_opt, const char *long_opt, const char *description, const bool required, t_opt_func func, const bool argument, t_opt_list *opt_list);
int opt_add_help(t_opt_list *opt_list);
void opt_print_help(const t_opt_list *opt_lists);

void debug_opt_list(t_opt_list *opt_lists);
void debug_opt(t_opt *opt);

int ft_getopt(const char **argv, const int argc, t_opt_list *opt_lists, void *obj);

void opt_print_completion(const t_opt_list *opt_lists, const char *prefix);

#endif
