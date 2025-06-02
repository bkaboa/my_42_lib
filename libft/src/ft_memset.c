#include "libft.h"

int ft_memset(void *addr, const u_int8_t c, size_t n)
{
    unsigned char *a = (unsigned char *)addr;

    if (addr == NULL)
        return (-1);
    while (n > 0)
    {
        *a = c;
        a++;
        n--;
    }
    return (0);
}