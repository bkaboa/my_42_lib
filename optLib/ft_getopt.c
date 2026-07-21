#include "optlib.h"

void opt_destroy(t_opt_list *opt_lists)
{
    t_opt *opt;
    t_opt *tmp;

    if (opt_lists == NULL)
        return;
    opt = opt_lists->head;
    while (opt != NULL)
    {
        tmp = opt;
        opt = opt->next;
        if (tmp->value != NULL)
            free(tmp->value);
        free(tmp);
    }
    if (opt_lists->main.value != NULL)
    {
        free(opt_lists->main.value);
        opt_lists->main.value = NULL;
    }
    if (opt_lists->empty_opt_arg.value != NULL)
    {
        free(opt_lists->empty_opt_arg.value);
        opt_lists->empty_opt_arg.value = NULL;
    }
    opt_lists->head = NULL;
    opt_lists->tail = NULL;
    ft_memset(opt_lists->by_short, 0, sizeof(opt_lists->by_short));
}

static int getOptError(t_opt_list *opt_lists, char *msg, const char *arg)
{
    if (msg)
    {
        if (arg != NULL)
            dprintf(STDERR_FILENO, "%sError: %s: %s%s\n", COLOR_RED, msg, arg, COLOR_RESET);
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
    dprintf(STDERR_FILENO, "%sFunction: %p%s\n", COLOR_BLUE, (void *)opt->func, COLOR_RESET);
    if (opt->value != NULL)
    {
        dprintf(STDERR_FILENO, "%sValue: %p%s\n", COLOR_BLUE, opt->value, COLOR_RESET);
        dprintf(STDERR_FILENO, "%sArray elem size: %zu%s\n", COLOR_BLUE, opt->arr_elem_size, COLOR_RESET);
    }
    dprintf(STDERR_FILENO, "%sNext: %p%s\n", COLOR_BLUE, (void *)opt->next, COLOR_RESET);
    dprintf(STDERR_FILENO, "%sPrev: %p%s\n", COLOR_BLUE, (void *)opt->prev, COLOR_RESET);
}

void debug_opt_list(t_opt_list *opt_lists)
{
    dprintf(STDERR_FILENO, "%sMain option: %s%s\n", COLOR_BLUE, opt_lists->main.description, COLOR_RESET);
    dprintf(STDERR_FILENO, "%sfunction: %p%s\n", COLOR_BLUE, (void *)opt_lists->main.func, COLOR_RESET);
    if (opt_lists->head == NULL)
    {
        dprintf(STDERR_FILENO, "No options\n");
        return;
    }
    t_opt *opt = opt_lists->head;
    dprintf(STDERR_FILENO, "--------------------------------------------\n");
    while (opt != NULL)
    {
        debug_opt(opt);
        dprintf(STDERR_FILENO, "--------------------------------------------\n");
        opt = opt->next;
    }
}

/**
 * set the main option of the list can be an array or a single value
 * @return OPT_SUCCESS on success, OPT_ERROR on failure
 */
int opt_set_main(t_opt_list *opt_list, const char description[], t_opt_func func)
{
    opt_list->main.short_opt = 0;
    opt_list->main.long_opt = NULL;
    opt_list->main.long_opt_len = 0;
    opt_list->main.description = (char *)description;
    opt_list->main.value = NULL;
    if (func != NULL)
    {
        opt_list->main.func = func;
        opt_list->main.is_set = false;
    }
    else
    {
        opt_list->main.func = NULL;
        opt_list->main.is_set = true;
    }
    opt_list->main.arr_elem_size = 0;
    opt_list->main.next = NULL;
    opt_list->main.prev = NULL;
    return (OPT_SUCCESS);
}

/**
 * add a new option to the list
 * @return OPT_SUCCESS on success, OPT_ERROR on failure
 */
int opt_add_new(const char short_opt, const char *long_opt, const char *description, const bool required, t_opt_func func, const bool argument, t_opt_list *opt_list)
{
    t_opt *tmp = opt_list->tail;
    t_opt *new_opt = malloc(sizeof(t_opt));

    if (new_opt == NULL)
        return (OPT_ERROR);
    new_opt->short_opt = (char)short_opt;
    new_opt->long_opt = (char *)long_opt;
    new_opt->long_opt_len = (long_opt != NULL) ? ft_strlen(long_opt) : 0;
    new_opt->description = (char *)description;
    new_opt->required = required;
    new_opt->argument = argument;
    new_opt->func = func;
    new_opt->arr_elem_size = 0;
    new_opt->value = NULL;
    new_opt->nb_value_elem = 0;
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
    if (short_opt != 0)
        opt_list->by_short[(unsigned char)short_opt] = new_opt;
    return (OPT_SUCCESS);
}

static int opt_help_func(const char *arg, void *obj)
{
    (void)arg;
    (void)obj;
    return (OPT_HELP);
}

/// Register -h / --help as a normal option (callback returns OPT_HELP).
int opt_add_help(t_opt_list *opt_list)
{
    return opt_add_new('h', "help", "Print this help", false, &opt_help_func, false, opt_list);
}

/// Set handler for bare positional args after main (e.g. `./program file1 file2`).
int opt_empty(t_opt_list *opt_list, const char *description, t_opt_func func)
{
    opt_list->empty_opt_arg.short_opt = 0;
    opt_list->empty_opt_arg.long_opt = NULL;
    opt_list->empty_opt_arg.long_opt_len = 0;
    opt_list->empty_opt_arg.description = (char *)description;
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

void opt_print_help(const t_opt_list *opt_lists)
{
    t_opt *opt;

    if (opt_lists == NULL)
        return;
    opt = opt_lists->head;
    if (opt_lists->main.description != NULL)
        dprintf(STDERR_FILENO, "%s\n", opt_lists->main.description);
    dprintf(STDERR_FILENO, "Options:\n");
    dprintf(STDERR_FILENO, "Usage: ./[program] [options]\n");
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

static int call_func(t_opt_list *opt_lists, t_opt *opt, const char *arg, void *obj)
{
    int ret;

    if (opt->func == NULL)
    {
        opt->is_set = true;
        return OPT_SUCCESS;
    }
    ret = opt->func(opt->argument ? arg : NULL, obj);
    if (ret == OPT_HELP)
    {
        opt_print_help(opt_lists);
        opt_destroy(opt_lists);
        return OPT_HELP;
    }
    if (ret == OPT_ERROR)
        return getOptError(opt_lists, NULL, NULL);
    opt->is_set = true;
    return OPT_SUCCESS;
}

void opt_print_completion(const t_opt_list *opt_lists, const char *prefix)
{
    bool only_long_opt;
    size_t prefix_len;
    const char *name;
    t_opt *opt;

    if (prefix == NULL || prefix[0] == '\0' || opt_lists == NULL || opt_lists->head == NULL)
        return;

    only_long_opt = (prefix[0] == '-' && prefix[1] == '-');
    name = only_long_opt ? prefix + 2 : (prefix[0] == '-' ? prefix + 1 : prefix);
    prefix_len = ft_strlen(name);
    opt = opt_lists->head;
    while (opt != NULL)
    {
        if (only_long_opt)
        {
            if (opt->long_opt != NULL && ft_strncmp(opt->long_opt, name, prefix_len) == 0)
                dprintf(STDOUT_FILENO, "--%s\n", opt->long_opt);
        }
        else
        {
            if (opt->short_opt != 0 && prefix[0] == '-' && prefix[1] == opt->short_opt)
                dprintf(STDOUT_FILENO, "-%c\n", opt->short_opt);
            if (opt->long_opt != NULL && ft_strncmp(opt->long_opt, name, prefix_len) == 0)
                dprintf(STDOUT_FILENO, "--%s\n", opt->long_opt);
        }
        opt = opt->next;
    }
}

static t_opt *find_long_opt(t_opt_list *list, const char *name, size_t name_len, bool *ambiguous)
{
    t_opt *opt = list->head;
    t_opt *exact = NULL;
    t_opt *prefix_match = NULL;
    int prefix_count = 0;

    *ambiguous = false;
    while (opt != NULL)
    {
        if (opt->long_opt != NULL)
        {
            if (opt->long_opt_len == name_len
                && ft_strncmp(opt->long_opt, name, name_len) == 0)
                exact = opt;
            else if (name_len > 0 && name_len < opt->long_opt_len
                && ft_strncmp(opt->long_opt, name, name_len) == 0)
            {
                prefix_count++;
                prefix_match = opt;
            }
        }
        opt = opt->next;
    }
    if (exact != NULL)
        return exact;
    if (prefix_count == 1)
        return prefix_match;
    if (prefix_count > 1)
    {
        *ambiguous = true;
        return NULL;
    }
    return NULL;
}

static int parse_long(t_opt_list *list, const char **argv, int argc, int *i, void *obj)
{
    const char *token = argv[*i] + 2;
    const char *eq = ft_strchr(token, '=');
    size_t name_len = (eq != NULL) ? (size_t)(eq - token) : ft_strlen(token);
    bool ambiguous = false;
    t_opt *opt;
    const char *arg_value;

    if (name_len == 0)
        return getOptError(list, "Invalid option", argv[*i]);

    opt = find_long_opt(list, token, name_len, &ambiguous);
    if (ambiguous)
        return getOptError(list, "Ambiguous option", argv[*i]);
    if (opt == NULL)
        return getOptError(list, "Invalid option", argv[*i]);

    if (opt->argument)
    {
        if (eq != NULL)
            arg_value = eq + 1;
        else
        {
            if (*i + 1 >= argc)
                return getOptError(list, "Missing argument", argv[*i]);
            (*i)++;
            arg_value = argv[*i];
        }
        return call_func(list, opt, arg_value, obj);
    }
    if (eq != NULL)
        return getOptError(list, "Unexpected argument", argv[*i]);
    return call_func(list, opt, NULL, obj);
}

static int parse_short_cluster(t_opt_list *list, const char **argv, int argc, int *i, void *obj)
{
    const char *token = argv[*i];
    int j = 1;
    t_opt *opt;
    const char *arg_value;
    int status;

    while (token[j] != '\0')
    {
        opt = list->by_short[(unsigned char)token[j]];
        if (opt == NULL)
            return getOptError(list, "Invalid option", argv[*i]);

        if (opt->argument)
        {
            if (token[j + 1] == '=')
                arg_value = token + j + 2;
            else if (token[j + 1] != '\0')
                arg_value = token + j + 1;
            else
            {
                if (*i + 1 >= argc)
                    return getOptError(list, "Missing argument", argv[*i]);
                (*i)++;
                arg_value = argv[*i];
            }
            return call_func(list, opt, arg_value, obj);
        }
        status = call_func(list, opt, NULL, obj);
        if (status != OPT_SUCCESS)
            return status;
        j++;
    }
    return OPT_SUCCESS;
}

static int parse_positional(t_opt_list *list, const char *arg, void *obj)
{
    int ret;

    if (list->main.is_set == false)
    {
        if (list->main.func == NULL)
            return getOptError(list, "Invalid argument", arg);
        ret = list->main.func(arg, obj);
        if (ret == OPT_ERROR)
            return getOptError(list, NULL, NULL);
        list->main.is_set = true;
        return OPT_SUCCESS;
    }
    if (list->empty_opt_arg.func != NULL)
    {
        ret = list->empty_opt_arg.func(arg, obj);
        if (ret == OPT_ERROR)
            return getOptError(list, NULL, NULL);
        list->empty_opt_arg.is_set = true;
        return OPT_SUCCESS;
    }
    return getOptError(list, "Invalid argument", arg);
}

static int check_required(t_opt_list *list)
{
    t_opt *opt = list->head;
    char short_buf[3];

    while (opt != NULL)
    {
        if (opt->required && !opt->is_set)
        {
            if (opt->long_opt != NULL)
                return getOptError(list, "Missing required option", opt->long_opt);
            if (opt->short_opt != 0)
            {
                short_buf[0] = '-';
                short_buf[1] = opt->short_opt;
                short_buf[2] = '\0';
                return getOptError(list, "Missing required option", short_buf);
            }
            return getOptError(list, "Missing required option", NULL);
        }
        opt = opt->next;
    }
    return OPT_SUCCESS;
}

/**
 * Parse command-line options.
 * Supports clustered short opts, --long[=arg], and `--` end-of-options.
 * @return OPT_SUCCESS, OPT_HELP, or OPT_ERROR
 */
int ft_getopt(const char **argv, const int argc, t_opt_list *opt_lists, void *obj)
{
    bool end_of_opts = false;
    int i = 1;
    int status;

    if (argv == NULL || opt_lists == NULL)
        return (OPT_ERROR);

    while (i < argc)
    {
        if (!end_of_opts && argv[i][0] == '-' && argv[i][1] != '\0')
        {
            if (argv[i][1] == '-' && argv[i][2] == '\0')
            {
                end_of_opts = true;
                i++;
                continue;
            }
            if (argv[i][1] == '-')
                status = parse_long(opt_lists, argv, argc, &i, obj);
            else
                status = parse_short_cluster(opt_lists, argv, argc, &i, obj);
            if (status != OPT_SUCCESS)
                return status;
        }
        else
        {
            status = parse_positional(opt_lists, argv[i], obj);
            if (status != OPT_SUCCESS)
                return status;
        }
        i++;
    }
    return check_required(opt_lists);
}
