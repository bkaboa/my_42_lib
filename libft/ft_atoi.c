#include "libft.h"

int ft_atoi(char *str)
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
        if (atol & 0x8000000000000000)
            return (-1);
    }
    if (sign)
        return (-atol);
    return (atol);
}