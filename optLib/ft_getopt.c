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
    t_opt *tmp;
    while(opt != NULL)
    {
        tmp = *opt;
        *opt = (*opt)->next;
        if (tmp->type & OPT_ARRAY)
        {
            if (tmp->value != NULL)
                free(tmp->value);
        }
        free(tmp);
    }
    *opt = NULL;
}

static void sanitize(t_opt *opt)
{
    t_opt *tmp;
    t_opt *tmp2;

    while (opt != NULL)
    {
        tmp = opt->next;
        if (tmp->active == false)
        {
            if (tmp->type & OPT_ARRAY)
            {
                if (tmp->value != NULL)
                    free(tmp->value);
                tmp->value = NULL;
            }
            if (tmp->next != NULL) {
                opt->next = tmp->next;
                tmp2 = tmp->next;
                tmp2->prev = opt;
            }
            free(tmp);
        }
    }
}

static int getOptError(t_opt *opt, char *msg)
{
    dprintf(STDERR_FILENO, "Error: %s\n", msg);
    opt_print_help(opt);
    opt_destroy(&opt);
    return (OPT_ERROR);
}

void debug_opt(t_opt *opt)
{
    while (opt != NULL)
    {
        dprintf(STDERR_FILENO, "opt address: %p\n", opt);
        dprintf(STDERR_FILENO, "next address: %p\n", opt->next);
        dprintf(STDERR_FILENO, "prev address: %p\n", opt->prev);
        dprintf(STDERR_FILENO, "short_opt: %c\n", opt->short_opt);
        dprintf(STDERR_FILENO, "long_opt: %s\n", opt->long_opt);
        dprintf(STDERR_FILENO, "description: %s\n", opt->description);
        dprintf(STDERR_FILENO, "type: %d\n", opt->type);
        dprintf(STDERR_FILENO, "arr_elem_size: %ld\n", opt->arr_elem_size);
        dprintf(STDERR_FILENO, "option: %ld\n", opt->option);
        dprintf(STDERR_FILENO, "active: %d\n", opt->active);
        if (opt->value == NULL)
            dprintf(STDERR_FILENO, "value: NULL\n");
        else {

            if (opt->type & OPT_ARRAY)
            {
                if (opt->type & OPT_LONG)
                {
                    for (int i = 0; i < opt->arr_elem_size; i++)
                        dprintf(STDERR_FILENO, "value[%d]: %ld\n", i, ((int64_t*)opt->value)[i]);
                }
                else if (opt->type & OPT_STRING)
                {
                    for (int i = 0; i < opt->arr_elem_size; i++)
                        dprintf(STDERR_FILENO, "value[%d]: %s\n", i, ((char**)opt->value)[i]);
                }
            }
            else
            {
                if (opt->type & OPT_LONG)
                    dprintf(STDERR_FILENO, "value: %ld\n", *((int64_t*)opt->value));
                else if (opt->type & OPT_STRING)
                    dprintf(STDERR_FILENO, "value: %s\n", *((char**)opt->value));
            }
        }
        dprintf(STDERR_FILENO, "\n-----------------------------------------------------------------------------\n");
        opt = opt->next;
    }
}

/**
 * @brief 
 * 
 * @param opt 
 * @param type 
 * @param description 
 * @return OPT_SUCCESS if the main option is set successfully //
 * @return OPT_ERROR if an error occured
 * 
 * set the main option of the list can be an array or a single value
 */
int opt_set_main(t_opt **opt, const enum opt_types type, const char description[])
{
    if (opt == NULL)
        return (OPT_ERROR);
    *opt = malloc(sizeof(t_opt));
    if (*opt == NULL)
        return (OPT_ERROR);
    (*opt)->short_opt = 0;
    (*opt)->long_opt = NULL;
    (*opt)->description = (char*)description;
    (*opt)->value = NULL;
    (*opt)->arr_elem_size = 0;
    (*opt)->active = true;
    (*opt)->type = type;
    (*opt)->next = NULL;
    (*opt)->prev = NULL;
    return (OPT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param short_opt 
 * @param long_opt 
 * @param type 
 * @param description 
 * @param opt 
 * @return OPT_SUCCESS if the option is added successfully //
 * @return OPT_ERROR if an error occured
 * 
 * add a new option to the list
 * 
 * you need to put character \'-\' before the short option or the long option
 */
int opt_add_new(const char short_opt, const char *long_opt, const enum opt_types type, const char *description, size_t option, t_opt *opt)
{
    if (opt == NULL)
        return (OPT_ERROR);
    t_opt *tmp = opt;
    t_opt *new_opt = malloc(sizeof(t_opt));
    if (new_opt == NULL)
        return (OPT_ERROR);
    new_opt->short_opt = (char)short_opt;
    new_opt->long_opt = (char*)long_opt;
    new_opt->description = (char*)description;
    new_opt->type = type;
    new_opt->arr_elem_size = 0;
    new_opt->value = NULL;
    new_opt->next = NULL;
    new_opt->option = option;
    while (opt->next != NULL)
        opt = opt->next;
    opt->next = new_opt;
    new_opt->prev = opt;
    return (OPT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param opt 
 * 
 * print the help of the options
 */
void opt_print_help(const t_opt *opt)
{
    while (opt != NULL)
    {
        if (opt->short_opt != 0)
            dprintf(STDERR_FILENO, "%c, ", opt->short_opt);
        if (opt->long_opt != NULL)
            dprintf(STDERR_FILENO, "%s, ", opt->long_opt);
        dprintf(STDERR_FILENO, "%s\n", opt->description);
        opt = opt->next;
    }
}

static int take_array(const char *arg, t_opt *opt)
{
    void *tmp = opt->value;
    opt->arr_elem_size += 1;
    if (opt->type & OPT_LONG)
    {
        if (ft_isnumber(arg) == 0) {
            dprintf(STDERR_FILENO, "Error: arg takes number\n", arg);
            return (OPT_ERROR);
        }
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
                ((char**)opt->value)[i] = (char*)arg;
            else
                ((char**)opt->value)[i] = ((char**)tmp)[i];
        }
    }
    return (OPT_SUCCESS);
}

static int take_arg(const char *arg, t_opt *opt)
{
    if (opt->type & OPT_ARRAY)
    {
        if (take_array(arg, opt) == OPT_ERROR) {
            return (OPT_ERROR);
        }
    }
    else if (opt->type == OPT_STRING)
    {
        char *str = (char*)arg;
        opt->value = &str;
    }
    else if (opt->type == OPT_LONG)
    {
        if (ft_isnumber(arg) == 0) {
            dprintf(STDERR_FILENO, "Error: arg takes number\n", arg);
            return (OPT_ERROR);
        }
        long num = ft_atol(arg);
        opt->value = &num;
    }
    else
    {
        return (OPT_ERROR);
    }
    return (OPT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param argv
 * @param argc 
 * @param opt 
 * @return OPT_SUCCESS if the options are taken successfully //
 * @return OPT_ERROR if an error occured
 * 
 * take the options from the command line
 * be aware the options list is sanitized after the call (remove the unused options)
 */
int ft_getopt(const char **argv, const int argc, t_opt *opt)
{
    if (argv == NULL || opt == NULL)
        return (OPT_ERROR);
    int i = 1;
    int j = 0;
    bool is_long_opt = false;
    t_opt *tmp = opt;
    while (i < argc)
    {
        opt = tmp;
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == '\0')
                return (getOptError(tmp, "Invalid option"));
            if (argv[i][1] == '-')
                is_long_opt = true;
            j = 1;
            while (opt->next != NULL && argv[i][j] != '\0') {
                if (is_long_opt == true) {
                    if (ft_strcmp(opt->long_opt, &(argv[i][2])) == 0) {
                        opt->active = true;
                        i += 1;
                        if (opt->type != OPT_NONE) {
                            if (take_arg(argv[i], opt) == OPT_ERROR) {
                                return (getOptError(tmp, "Invalid argument"));
                            }
                            break;
                        }
                    }
                }
                else {
                    if (opt->short_opt == argv[i][j]) {
                        opt->active = true;
                        if (opt->type != OPT_NONE) {
                            i += 1;
                            if (take_arg(argv[i], opt) == OPT_ERROR) {
                                return (getOptError(tmp, "Invalid argument"));
                            }
                            break;
                        }
                        j += 1;
                        opt = tmp;
                    }
                }
                opt = opt->next;
                if (opt->next == NULL) {
                    return (getOptError(tmp, "Invalid option"));
                }
            }
            i += 1;
        }
        else
        {
            if (opt->value != NULL && !(opt->type & OPT_ARRAY)) {
                return (getOptError(tmp, "main argument already set"));
            }
            if (take_arg(argv[i], opt) == OPT_ERROR) {
                return (getOptError(tmp, "Invalid argument"));
            }
        }
        i++;
    }
    if (tmp->value == NULL) {
        return (getOptError(tmp, "main argument not set"));
    }
    sanitize(tmp);
    return (OPT_SUCCESS);
}