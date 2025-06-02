#include "libft.h"

int ft_memcmp(const void *addr1, const void *addr2, size_t n)
{
    unsigned char *a1 = (unsigned char *)addr1;
    unsigned char *a2 = (unsigned char *)addr2;

    if (addr1 == NULL && addr2 == NULL)
        return (0);
    if (addr1 == NULL || addr2 == NULL)
        return (-1);
    while (n > 0)
    {
        if (*a1 != *a2)
            return (*a1 - *a2);
        a1++;
        a2++;
        n--;
    }
    return (0);
}