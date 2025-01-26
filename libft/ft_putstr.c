#include "libft.h"

void ft_putstr(char *str)
{
    if (str == NULL)
        return;
    while (*str)
    {
        write(1, str, 1);
        str++;
    }
}