#include "libft.h"

int ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    unsigned char *s = (unsigned char *)src;

    if (dst == NULL || src == NULL)
        return (-1);
    while (n > 0)
    {
        *d = *s;
        d++;
        s++;
        n--;
    }
    return (0);
}