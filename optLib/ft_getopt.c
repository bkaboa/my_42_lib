#include "optlib.h"

void opt_destroy(t_opt_list opt_lists)
{
    t_opt *opt = opt_lists.head;
    t_opt *tmp;
    while(opt != NULL)
    {
        tmp = opt;
        opt = opt->next;
        if (tmp->value != NULL)
            free(tmp->value);
        free(tmp);
    }
    if (opt_lists.main.value != NULL)
        free(opt_lists.main.value);
    opt_lists.head = NULL;
    opt_lists.tail = NULL;
}

static int getOptError(t_opt_list opt_lists, char *msg, const char *arg)
{
    if (msg)
    {
        if (arg != NULL)
            dprintf(STDERR_FILENO, "%sError: %s: %s%s\n",COLOR_RED, msg, arg, COLOR_RESET);
        else
            dprintf(STDERR_FILENO, "%sError: %s%s\n", COLOR_RED, msg, COLOR_RESET);
    }
    opt_print_help(opt_lists);
    opt_destroy(opt_lists);
    return (OPT_ERROR);
}

void debug_opt(t_opt *opt)
{
    dprintf(STDERR_FILENO, "%sShort option: %c%s\n", COLOR_BLUE, opt->short_opt, COLOR_RESET);
    dprintf(STDERR_FILENO, "%sLong option: %s%s\n", COLOR_BLUE, opt->long_opt, COLOR_RESET);
    dprintf(STDERR_FILENO, "%sDescription: %s%s\n", COLOR_BLUE, opt->description, COLOR_RESET);
    dprintf(STDERR_FILENO, "%sRequired: %s%s\n", COLOR_BLUE, opt->required ? "true" : "false", COLOR_RESET);
    dprintf(STDERR_FILENO, "%sArgument: %s%s\n", COLOR_BLUE, opt->argument ? "true" : "false", COLOR_RESET);
    dprintf(STDERR_FILENO, "%sFunction: %p%s\n", COLOR_BLUE, opt->func, COLOR_RESET);
    if (opt->value != NULL)
    {
        dprintf(STDERR_FILENO, "%sValue: %p%s\n", COLOR_BLUE, opt->value, COLOR_RESET);
        dprintf(STDERR_FILENO, "%sArray elem size: %zu%s\n", COLOR_BLUE, opt->arr_elem_size, COLOR_RESET);
    }
    dprintf(STDERR_FILENO, "%sNext: %p%s\n", COLOR_BLUE, opt->next, COLOR_RESET);
    dprintf(STDERR_FILENO, "%sPrev: %p%s\n", COLOR_BLUE, opt->prev, COLOR_RESET);
}

void debug_opt_list(t_opt_list *opt_lists)
{
    dprintf(STDERR_FILENO, "%sMain option: %s%s\n", COLOR_BLUE, opt_lists->main.description, COLOR_RESET);
    dprintf(STDERR_FILENO, "%sfunction: %p%s\n", COLOR_BLUE, opt_lists->main.func, COLOR_RESET);
    if (opt_lists->head == NULL)
    {
        dprintf(STDERR_FILENO, "No options\n");
        return;
    }
    else
    {
        t_opt *opt = opt_lists->head;
        dprintf(STDERR_FILENO, "--------------------------------------------\n");
        while (opt != NULL)
        {
            debug_opt(opt);
            dprintf(STDERR_FILENO, "--------------------------------------------\n");
            opt = opt->next;
        }
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
int opt_set_main(t_opt_list *opt_list, const char description[], void *(*func)(const char *arg, void *obj))
{
    opt_list->main.short_opt = 0;
    opt_list->main.long_opt = NULL;
    opt_list->main.description = (char*)description;
    opt_list->main.value = NULL;
    opt_list->main.func = func;
    opt_list->main.arr_elem_size = 0;
    opt_list->main.next = NULL;
    opt_list->main.prev = NULL;
    opt_list->main.is_set = false;
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
int opt_add_new(const char short_opt, const char *long_opt, const char *description, const bool required, void *(*func)(const char *arg, void *obj), const bool argument, t_opt_list *opt_list)
{
    t_opt *tmp = opt_list->tail;
    t_opt *new_opt = malloc(sizeof(t_opt));
    if (new_opt == NULL)
        return (OPT_ERROR);
    new_opt->short_opt = (char)short_opt;
    new_opt->long_opt = (char*)long_opt;
    new_opt->description = (char*)description;
    new_opt->required = required;
    new_opt->argument = argument;
    new_opt->func = func;
    new_opt->arr_elem_size = 0;
    new_opt->value = NULL;
    new_opt->next = NULL;
    new_opt->prev = NULL;
    new_opt->is_set = false;
    if (opt_list->head == NULL)
    {
        opt_list->head = new_opt;
        opt_list->tail = new_opt;
    }
    else
    {
        tmp->next = new_opt;
        new_opt->prev = tmp;
        opt_list->tail = new_opt;
    }
    return (OPT_SUCCESS);
}

/// @brief this function is used to set the empty option argument like `./program file1 file2`
/// @param opt_list 
/// @param description 
/// @param func 
/// @return OPT_SUCCESS if the empty option is set successfully //
/// @return OPT_ERROR if an error occured
int opt_empty(t_opt_list *opt_list, const char *description, void *(*func)(const char *arg, void *obj))
{
    opt_list->empty_opt_arg.short_opt = 0;
    opt_list->empty_opt_arg.long_opt = NULL;
    opt_list->empty_opt_arg.description = (char*)description;
    opt_list->empty_opt_arg.value = NULL;
    opt_list->empty_opt_arg.func = func;
    opt_list->empty_opt_arg.arr_elem_size = 0;
    opt_list->empty_opt_arg.next = NULL;
    opt_list->empty_opt_arg.prev = NULL;
    opt_list->empty_opt_arg.is_set = false;
    opt_list->empty_opt_arg.required = false;
    opt_list->empty_opt_arg.argument = false;
    return (OPT_SUCCESS);
}

/**
 * @brief
 *
 * @param opt
 *
 * print the help of the options
 */
void opt_print_help(const t_opt_list opt_lists)
{
    t_opt *opt = opt_lists.head;

    dprintf(STDERR_FILENO, "%s\n", opt_lists.main.description);
    dprintf(STDERR_FILENO, "Options:\n");
    dprintf(STDERR_FILENO, "Usage: ./[program] [options]\n");
    dprintf(STDERR_FILENO, "-h     --help,     Print this help\n");
    while (opt != NULL)
    {
        if (opt->short_opt != 0)
            dprintf(STDERR_FILENO, "-%c     ", opt->short_opt);
        if (opt->long_opt != NULL)
            dprintf(STDERR_FILENO, "--%s,  ", opt->long_opt);
        dprintf(STDERR_FILENO, "%s\n", opt->description);
        opt = opt->next;
    }
}

static int call_func(t_opt_list opt_lists, t_opt *opt, const char *arg, void *obj)
{
    if (opt->func == NULL)
    {
        return OPT_SUCCESS;
    }
    if (opt->argument)
    {
        if ((long)opt->func((void*)arg, obj) == OPT_ERROR)
        {
            return getOptError(opt_lists, NULL, NULL);
        }
    }
    else
    {
        if ((long)opt->func(NULL, obj) == OPT_ERROR)
        {
            return getOptError(opt_lists, NULL, NULL);
        }
    }
    return OPT_SUCCESS;
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
int ft_getopt(const char **argv, const int argc, t_opt_list opt_lists, void *obj) {
    if (argv == NULL)
        return (OPT_ERROR);

    t_opt *opt = opt_lists.head;
    int i = 1;

    while (i < argc) {
        opt = opt_lists.head;
        if (argv[i][0] == '-')
        {
            bool is_long_opt = (argv[i][1] == '-');
            int j = is_long_opt ? 2 : 1;

            while (opt != NULL && argv[i][j] != '\0')
            {
                if (is_long_opt)
                {
                    if (ft_strncmp(argv[i] + j, "help", 4) == 0)
                    {
                        opt_print_help(opt_lists);
                        opt_destroy(opt_lists);
                        return (OPT_ERROR);
                    }
                    if (ft_strncmp(opt->long_opt, argv[i] + j, ft_strlen(opt->long_opt)) == 0 && opt->long_opt != NULL)
                    {
                        if (opt->argument)
                        {
                            const char *arg_value = ft_strchr(argv[i] + j, '=');
                            if (arg_value == NULL)
                            {
                                if (i + 1 >= argc)
                                {
                                    return getOptError(opt_lists, "Missing argument", argv[i]);
                                }
                                arg_value = (char*)argv[i + 1];
                                i++;
                            }
                            else
                            {
                                arg_value++;
                            }
                            if (call_func(opt_lists, opt, arg_value, obj) == OPT_ERROR)
                            {
                                return OPT_ERROR;
                            }
                        }
                        else
                        {
                            if (call_func(opt_lists, opt, NULL, obj) == OPT_ERROR)
                            {
                                return OPT_ERROR;
                            }
                        }
                        break;
                    }
                }
                else
                {
                    if (argv[i][j] == 'h')
                    {
                        opt_print_help(opt_lists);
                        opt_destroy(opt_lists);
                        return (OPT_ERROR);
                    }
                    if (opt->short_opt == argv[i][j] && opt->short_opt != 0)
                    {
                        if (opt->argument)
                        {
                            const char *arg_value = (argv[i][j + 1] == '=') ? argv[i] + j + 2 : argv[i] + j + 1;
                            if (argv[i][j + 1] == '\0')
                            {
                                if (i + 1 >= argc)
                                {
                                    return getOptError(opt_lists, "Missing argument", argv[i]);
                                }
                                arg_value = argv[i + 1];
                                i++;
                            }
                            if (call_func(opt_lists, opt, arg_value, obj) == OPT_ERROR)
                            {
                                return OPT_ERROR;
                            }
                            break;
                        }
                        else
                        {
                            if (call_func(opt_lists, opt, NULL, obj) == OPT_ERROR)
                            {
                                return OPT_ERROR;
                            }
                            if (argv[i][j + 1] == '\0')
                            {
                                break;
                            }
                            j++;
                            opt = opt_lists.head;
                            continue;
                        }
                    }
                }
                opt = opt->next;
            }
            if (opt == NULL)
            {
                return getOptError(opt_lists, "Invalid option", argv[i]);
            }
        }
        else if (opt_lists.main.is_set == false)
        {
            opt_lists.main.is_set = true;
            if ((long)opt_lists.main.func(argv[i], obj) == OPT_ERROR)
            {
                return getOptError(opt_lists, NULL, NULL);
            }
        }
        else if (opt_lists.empty_opt_arg.func != NULL)
        {
            if ((long)opt_lists.empty_opt_arg.func(argv[i], obj) == OPT_ERROR)
            {
                return getOptError(opt_lists, NULL, NULL);
            }
        }
        else
        {
            return getOptError(opt_lists, "Invalid argument", argv[i]);
        }
        i++;
    }
    return OPT_SUCCESS;
}