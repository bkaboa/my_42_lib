#include "libft.h"

int ft_strdup(char **dest, const char *src)
{
    size_t len = ft_strlen(src);
    *dest = malloc(len + 1);
    if (*dest == NULL)
        return (-1);
    ft_memcpy(*dest, src, len);
    (*dest)[len] = '\0';
    return (0);
}

int ft_strndup(char **dest, const char *src, size_t n)
{
    size_t len = ft_strlen(src);
    if (len > n)
        len = n;
    *dest = malloc(len + 1);
    if (*dest == NULL)
        return (-1);
    ft_memcpy(*dest, src, len);
    (*dest)[len] = '\0';
    return (0);
}