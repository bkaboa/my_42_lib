#include "libft.h"

void ft_swap(void *addr, void *addr2) {
    void *tmp;

    if (addr == NULL || addr2 == NULL)
        return;
    tmp = addr;
    addr = addr2;
    addr2 = tmp;
}