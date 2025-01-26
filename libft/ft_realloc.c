#include "libft.h"

int ft_realloc(void **ptr, size_t size)
{
    void *new_ptr = NULL;

    if (ptr == NULL)
        return (-1);
    if (size == 0)
    {
        free(*ptr);
        *ptr = NULL;
        return (0);
    }
    new_ptr = malloc(size);
    if (new_ptr == NULL)
        return (-1);
    if (*ptr != NULL)
    {
        ft_memcpy(new_ptr, *ptr, size);
        free(*ptr);
    }
    *ptr = new_ptr;
    return (0);
}