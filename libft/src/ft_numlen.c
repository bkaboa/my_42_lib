#include "libft.h"

size_t ft_numlen(ssize_t n)
{
    size_t len = 0;

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
    return len;
}

size_t ft_numlen_base(ssize_t n, size_t base)
{
    size_t len = 0;

    if (n < 0)
    {
        n = -n;
        len++;
    }
    while (n > 0)
    {
        n /= base;
        len++;
    }
    return len;
}