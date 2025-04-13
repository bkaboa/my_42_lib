#include "libft.h"

int ft_numlen(int n)
{
    int len;

    len = 0;
    if (n < 0)
    {
        n = -n;
        len++;
    }
    while (n > 0)
    {
        n /= 10;
        len++;
    }
    return (len);
}