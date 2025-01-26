#include "libft.h"

char *ft_strjoin(const char *str1, const char *str2)
{
    size_t len1 = ft_strlen(str1);
    size_t len2 = ft_strlen(str2);
    char *new_str = malloc(len1 + len2 + 1);
    if (new_str == NULL)
        return (NULL);
    ft_memcpy(new_str, str1, len1);
    ft_memcpy(new_str + len1, str2, len2);
    new_str[len1 + len2] = '\0';
    return (new_str);
}