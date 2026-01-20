#include "libft.h"

int ft_strcat(char *dest, const char *src)
{
    size_t dest_len = ft_strlen(dest);
    size_t src_len = ft_strlen(src);
    size_t i = 0;

    if (dest == NULL || src == NULL)
        return (-1);
    while (i < src_len)
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return (0);
}

int ft_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = ft_strlen(dest);
    size_t src_len = ft_strlen(src);
    size_t i = 0;

    while (i < src_len && i < n)
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return (0);
}