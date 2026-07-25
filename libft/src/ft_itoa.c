#include "libft.h"
#include <stddef.h>

char *ft_itoa(const int n)
{
    char    *str;
    size_t     len;
    bool    is_negative = false;
    ssize_t    num = n;

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
            if (num > (ssize_t)-10)
                num = -num;
        }
        str[len] = num % 10 + '0';
        num /= 10;
    }
    if (is_negative)
        str[0] = '-';
    return (str);
}

char *ft_itoa_base(const int n, const char *base)
{
    char *str;
    size_t len;
    size_t base_len;
    bool is_negative = false;
    ssize_t num = n;

    if (n < 0)
    {
        is_negative = true;

    }
    base_len = ft_strlen(base);
    len = ft_numlen_base(num , base_len) + (is_negative ? 1 : 0);
    str = malloc(sizeof(char) * len + 1);
    if (!str)
        return NULL;
    str[len] = '\0';
    while (len--)
    {
        if (is_negative)
        {
            if (num > (ssize_t)-base_len)
                num = -num;
        }
        str[len] = base[num % base_len];
        num /= base_len;
    }
    if (is_negative)
        str[0] = '-';
    return str;
}