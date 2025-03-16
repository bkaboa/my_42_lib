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

static int getOptError(t_opt_list opt_lists, char *msg)
{
    dprintf(STDERR_FILENO, "Error: %s\n", msg);
    opt_print_help(opt_lists);
    opt_destroy(opt_lists);
    return (OPT_ERROR);
}

// void debug_opt_list(t_opt_list opt_lists)
// {
//     while (opt != NULL)
//     {
//         dprintf(STDERR_FILENO, "opt address: %p\n", opt);
//         dprintf(STDERR_FILENO, "next address: %p\n", opt->next);
//         dprintf(STDERR_FILENO, "prev address: %p\n", opt->prev);
//         dprintf(STDERR_FILENO, "short_opt: %c\n", opt->short_opt);
//         dprintf(STDERR_FILENO, "long_opt: %s\n", opt->long_opt);
//         dprintf(STDERR_FILENO, "description: %s\n", opt->description);
//         dprintf(STDERR_FILENO, "arr_elem_size: %ld\n", opt->arr_elem_size);
//         if (opt->value == NULL)
//             dprintf(STDERR_FILENO, "value: NULL\n");
//         dprintf(STDERR_FILENO, "\n-----------------------------------------------------------------------------\n");
//         opt = opt->next;
//     }
// }

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
int opt_set_main(t_opt_list *opt_list, const char description[], void *(*func)(void*))
{
    opt_list->main.short_opt = 0;
    opt_list->main.long_opt = NULL;
    opt_list->main.description = (char*)description;
    opt_list->main.value = NULL;
    opt_list->main.func = func;
    opt_list->main.arr_elem_size = 0;
    opt_list->main.next = NULL;
    opt_list->main.prev = NULL;
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
int opt_add_new(const char short_opt, const char *long_opt, const char *description, const bool required, void *(*func)(void*), const bool argument, t_opt_list opt_list)
{
    t_opt *tmp = opt_list.tail;
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
    if (opt_list.head == NULL)
    {
        opt_list.head = new_opt;
        opt_list.tail = new_opt;
    }
    else
    {
        tmp->next = new_opt;
        new_opt->prev = tmp;
        opt_list.tail = new_opt;
    }
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
    dprintf(STDERR_FILENO, "Usage: ./program [options]\n");
    dprintf(STDERR_FILENO, "-h, --help     Print this help\n");
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

static int process_long_option(t_opt_list opt_lists, t_opt *opt, const char *arg, const int argc, int *i)
{
    if (opt->argument)
    {
        const char *arg_value = (arg[0] == '=') ? arg + 1 : arg;
        if (arg[0] == '\0')
        {
            if (*i + 1 >= argc)
            {
                return getOptError(opt_lists, "Missing argument");
            }
            arg_value = arg + 1;
            (*i)++;
        }
        if (call_func(opt_lists, opt, arg_value) == OPT_ERROR)
        {
            return OPT_ERROR;
        }
    }
    else
    {
        if (call_func(opt_lists, opt, NULL) == OPT_ERROR)
        {
            return OPT_ERROR;
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
int ft_getopt(const char **argv, const int argc, t_opt_list opt_lists) {
    if (argv == NULL || opt_lists.head == NULL)
        return (OPT_ERROR);

    t_opt *opt = opt_lists.head;
    int i = 1;

    while (i < argc) {
        if (ft_strncmp(argv[i], "--help", 6) == 0 || ft_strncmp(argv[i], "-h", 2) == 0) {
            opt_print_help(opt_lists);
            opt_destroy(opt_lists);
            return (OPT_HELP);
        }

        opt = opt_lists.head;
        if (argv[i][0] == '-')
        {
            bool is_long_opt = (argv[i][1] == '-');
            int j = is_long_opt ? 2 : 1;

            while (opt != NULL && argv[i][j] != '\0')
            {
                if (is_long_opt)
                {
                    if (ft_strncmp(opt->long_opt, argv[i] + j, ft_strlen(opt->long_opt)) == 0)
                    {
                        int result = process_long_option(opt_lists, opt, argv[i] + j, argc, &i);
                        if (result != OPT_SUCCESS)
                        {
                            return result;
                        }
                        break;
                    }
                }
                else
                {
                    if (opt->short_opt == argv[i][j])
                    {
                        if (opt->argument)
                        {
                            const char *arg_value = (argv[i][j + 1] == '=') ? argv[i] + j + 2 : argv[i] + j + 1;
                            if (argv[i][j + 1] == '\0')
                            {
                                if (i + 1 >= argc)
                                {
                                    return getOptError(opt_lists, "Missing argument");
                                }
                                arg_value = argv[i + 1];
                                i++;
                            }
                            if (call_func(opt_lists, opt, arg_value) == OPT_ERROR)
                            {
                                return OPT_ERROR;
                            }
                            break;
                        }
                        else
                        {
                            if (call_func(opt_lists, opt, NULL) == OPT_ERROR)
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
                return getOptError(opt_lists, "Invalid option");
            }
        }
        i++;
    }
    return OPT_SUCCESS;
}