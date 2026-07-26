#include "libft.h"
#include <stddef.h>

char *ft_ultoa_base(const size_t n, const char *base)
{
    char *str;
    size_t len;
    size_t base_len;
    size_t num = n;

    base_len = ft_strlen(base);
    len = ft_numlen_base(num , base_len);
    str = malloc(sizeof(char) * len + 1);
    if (!str)
        return NULL;
    str[len] = '\0';
    while (len--)
    {
        str[len] = base[num % base_len];
        num /= base_len;
    }
    return str;
}

char *ft_ultoa(const size_t n)
{
    return ft_ultoa_base(n, BASE_10);
}

char *ft_ltoa_base(const ssize_t n, const char *base)
{
    char *str;
    size_t len;
    size_t base_len;
    bool is_negative = false;
    ssize_t num = n;

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

char *ft_ltoa(const ssize_t n)
{
    return ft_ltoa_base(n, BASE_10);
}

char *ft_itoa_base(const int n, const char *base)
{
    return ft_ltoa_base(n, base);
}

char *ft_itoa(const int n)
{
    return ft_itoa_base(n, BASE_10);
}


