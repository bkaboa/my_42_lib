#include "libft.h"

int ft_atoi(const char *str)
{
    int atol = 0;
    int sign = 0;

    if (str == NULL)
        return (-1);

    if (*str == '-')
    {
        sign = 1;
        str++;
    }

    while (*str && *str >= '0' && *str <= '9')
    {
        atol *= 10;
        atol += (*str - '0');
        str++;
        if (atol & 0x80000000)
            return (-1);
    }
    if (sign)
        return (-atol);
    return (atol);
}

long ft_atol(const char *str)
{
    long atol = 0;
    int sign = 0;

    if (str == NULL)
        return (-1);

    if (*str == '-')
    {
        sign = 1;
        str++;
    }

    while (*str && *str >= '0' && *str <= '9')
    {
        atol *= 10;
        atol += (*str - '0');
        str++;
        if (atol & 0x8000000000000000)
            return (-1);
    }
    if (sign)
        return (-atol);
    return (atol);
}

int ft_atoi_base(const char *str, int base)
{
    int atol = 0;
    int sign = 0;

    if (str == NULL)
        return (-1);

    if (*str == '-')
    {
        sign = 1;
        str++;
    }

    while (*str)
    {
        if (*str >= '0' && *str <= '9')
        {
            atol *= base;
            atol += (*str - '0');
        }
        else if (*str >= 'A' && *str <= 'F')
        {
            atol *= base;
            atol += (*str - 'A' + 10);
        }
        else if (*str >= 'a' && *str <= 'f')
        {
            atol *= base;
            atol += (*str - 'a' + 10);
        }
        else
            return (-1);
        str++;
        if (atol & 0x8000000000000000)
            return (-1);
    }
    if (sign)
        return (-atol);
    return (atol);
}