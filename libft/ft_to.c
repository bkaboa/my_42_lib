#include "libft.h"

int ft_strToupper(char *str)
{
    if (str == NULL)
        return (-1);
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
            *str -= 32;
        str++;
    }
    return (0);
}

int ft_strTolower(char *str)
{
    if (str == NULL)
        return (-1);
    while (*str)
    {
        if (*str >= 'A' && *str <= 'Z')
            *str += 32;
        str++;
    }
    return (0);
}

int ft_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}

int ft_toupper(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}

int ft_toascii(int c)
{
    return (c & 0x7F);
}

int ft_tochar(int c)
{
    return (c & 0xFF);
}