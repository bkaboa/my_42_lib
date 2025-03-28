#include "libft.h"

bool ft_isnumber(const char *str)
{
    if (str == NULL)
        return (false);
    if (*str == '-' || *str == '+') {
        str++;
        if (*str == '\0')
            return false;
    }
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return false;
        str++;
    }
    return true;
}

bool ft_isdecimal(const char *str)
{
    void *dec_addr = NULL;
    void *exp_addr = NULL;

    if (str == NULL)
        return (false);

    while (*str)
    {
        if (*str < '0' || *str > '9')
        {
            if (*str == '.')
            {
                if (dec_addr)
                {
                    return (false);
                }
                dec_addr = (void*)str;
            }
            else if (*str == 'e' || *str == 'E')
            {
                if (exp_addr)
                    return (false);
                exp_addr = (void*)str;
            }
            else
                return (false);
        }
        str++;
    }

    if (dec_addr == str || dec_addr == NULL)
        return (false);

    return (true);
}

bool ft_ishex(const char *str)
{
    if (str == NULL)
        return (false);
    if (*str == '\0')
        return (false);
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
        str += 2;
    while (*str) {
        if (!ft_isdigit(*str) && !(*str >= 'a' && *str <= 'f') && !(*str >= 'A' && *str <= 'F'))
            return (false);
        str++;
    }
    return (true);
}

bool ft_isdigit(const int c)
{
    return (c >= '0' && c <= '9');
}

bool ft_isalpha(const int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool ft_isalnum(const int c)
{
    return (ft_isdigit(c) || ft_isalpha(c));
}

bool ft_isascii(const int c)
{
    return (c >= 0 && c <= 127);
}

bool ft_isprint(const int c)
{
    return (c >= 32 && c <= 126);
}

bool ft_isspace(const int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

bool ft_islower(const int c)
{
    return (c >= 'a' && c <= 'z');
}

bool ft_isupper(const int c)
{
    return (c >= 'A' && c <= 'Z');
}

bool ft_isblank(const int c)
{
    return (c == ' ' || c == '\t');
}

bool ft_iscntrl(const int c)
{
    return (c >= 0 && c <= 31);
}

bool ft_isgraph(const int c)
{
    return (c >= 33 && c <= 126);
}

bool ft_ispunct(const int c)
{
    return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126));
}
