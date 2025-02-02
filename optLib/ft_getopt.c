#include "optlib.h"

static void freeArray(t_opt *opt)
{
    while (opt != NULL) {
        if (opt->type & OPT_ARRAY)
        {
            if (opt->value != NULL)
                free(opt->value);
            opt->value = NULL;
        }
        opt = opt->next;
    }
}

static void free_opt(t_opt *opt)
{
    while (opt->next != NULL)
    {
        opt = opt->next;
        free(opt->prev);
    }
    free(opt);
}

void opt_destroy(t_opt **opt)
{
    freeArray(*opt);
    free_opt(*opt);
    *opt = NULL;
}

int opt_set_main(t_opt **opt, const enum opt_types type, const char *description)
{
    if (opt == NULL)
        return (OPT_ERROR);
    *opt = malloc(sizeof(t_opt));
    if (*opt == NULL)
        return (OPT_ERROR);
    (*opt)->short_opt = NULL;
    (*opt)->long_opt = NULL;
    (*opt)->description = description;
    (*opt)->value = NULL;
    (*opt)->type = type;
    (*opt)->next = NULL;
    (*opt)->prev = NULL;
}

int opt_add_new(const char *short_opt, const char *long_opt, const enum opt_types type, const char *description, t_opt *opt)
{
    if (opt == NULL)
        return (OPT_ERROR);
    t_opt *tmp = opt;
    t_opt *new_opt = malloc(sizeof(t_opt));
    if (new_opt == NULL)
        return (OPT_ERROR);
    new_opt->short_opt = short_opt;
    new_opt->long_opt = long_opt;
    new_opt->description = description;
    new_opt->type = type;
    new_opt->arr_elem_size = 0;
    new_opt->value = NULL;
    new_opt->next = NULL;
    new_opt->prev = opt;
    while (opt->next != NULL)
        opt = opt->next;
    opt->next = new_opt;
}

void opt_print_help(const t_opt *opt)
{
    while (opt != NULL)
    {
        if (opt->short_opt != NULL)
            printf("%s, ", opt->short_opt);
        if (opt->long_opt != NULL)
            printf("%s, ", opt->long_opt);
        printf("%s\n", opt->description);
        opt = opt->next;
    }
}

static int take_array(const char *arg, t_opt *opt)
{
    void *tmp = opt->value;
    opt->arr_elem_size += 1;
    if (opt->type & OPT_LONG)
    {
        if (ft_isnumber(arg) == 0)
            return (OPT_ERROR);
        opt->value = malloc(sizeof(int64_t) * opt->arr_elem_size);
        if (opt->value == NULL)
            return (OPT_ERROR);
        for (int i = 0; i < opt->arr_elem_size; i++)
        {
            if (i == opt->arr_elem_size - 1)
                ((int64_t*)opt->value)[i] = ft_atol(arg);
            else
                ((int64_t*)opt->value)[i] = ((int64_t*)tmp)[i];
        }
    }
    else if (opt->type & OPT_STRING)
    {
        opt->value = malloc(sizeof(char*) * opt->arr_elem_size);
        if (opt->value == NULL)
            return (OPT_ERROR);
        for (int i = 0; i < opt->arr_elem_size; i++)
        {
            if (i == opt->arr_elem_size - 1)
                ((char**)opt->value)[i] = arg;
            else
                ((char**)opt->value)[i] = ((char**)tmp)[i];
        }
    }
}

static int take_arg(const char *arg, t_opt *opt)
{
    opt->active = true;
    if (opt->type & OPT_ARRAY)
    {
         take_array(arg, opt);
         if (opt->value == NULL)
         {
             printf("Error while taking array\n");
             opt_destroy(opt);
             return (OPT_ERROR);
         }
    }
    if (opt->type == OPT_STRING)
    {
        *((char **)opt->value) = arg;
    }
    else if (opt->type == OPT_LONG)
    {
        if (ft_isnumber(arg) == 0)
        {
            printf("Invalid argument: %s\n", arg);
            print_help(opt);
            opt_destroy(opt);
            return (OPT_ERROR);
        }
        *((int64_t *)opt->value) = ft_atol(arg);
    }
    else
    {
        return (OPT_ERROR);
    }
}

int ft_getopt(const char **args, const int argc, t_opt *opt)
{
    if (args == NULL || opt == NULL)
        return (OPT_ERROR);
    int i = 1;
    t_opt *tmp = opt;
    while (i < argc)
    {
        opt = tmp;
        if (args[i][0] == '-')
        {
            while (opt->next != NULL)
            {
                if (opt->short_opt != NULL && ft_strcmp(opt->short_opt, args[i]) == 0)
                {
                    i += 1;
                    if (take_arg(args, opt) == OPT_ERROR)
                        return (OPT_ERROR);
                    break;
                }
                else if (opt->long_opt != NULL && ft_strcmp(opt->long_opt, args[i]) == 0)
                {
                    i += 1;
                    if (take_arg(args, opt) == OPT_ERROR)
                        return (OPT_ERROR);
                    break;
                }
                opt = opt->next;
                if (opt->next == NULL)
                {
                    printf("Invalid option: %s\n", args[i]);
                    print_help(tmp);
                    free_opt(tmp);
                    return (OPT_ERROR);
                }
                i += 1;
            }
        }
        else
        {
            if (opt->value != NULL && !(opt->type & OPT_ARRAY)) {
                printf("can't redefine main argument\n");
                opt_print_help(tmp);
                free_opt(tmp);
                return (OPT_ERROR);
            }
            take_arg(args, opt);
        }
        i++;
    }
    return (OPT_SUCCESS);
}