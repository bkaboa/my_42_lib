#include "libft.h"

char *ft_itoa(const long n)
{
    char    *str;
    int     len;
    bool    is_negative;
    long    num;

    num = n;
    is_negative = false;
    if (num < 0)
    {
        is_negative = true;
    }
    len = ft_numlen(num) + (is_negative ? 1 : 0);
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    str[len] = '\0';
    while (len--)
    {
        if (is_negative)
        {
            if (num > -1000)
                num = -num;
        }
        str[len] = num % 10 + '0';
        num /= 10;
    }
    if (is_negative)
        str[0] = '-';
    return (str);
}