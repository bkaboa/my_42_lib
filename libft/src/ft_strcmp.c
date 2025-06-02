#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL)
        return (0);
    if (s1 == NULL || s2 == NULL)
        return (-1);
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    if (s1 == NULL && s2 == NULL)
        return (0);
    if (s1 == NULL || s2 == NULL)
        return (-1);
    while (*s1 && *s2 && *s1 == *s2 && n > 0)
    {
        s1++;
        s2++;
        n--;
    }
    return (*s1 - *s2);
}

int ft_strcoll(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL)
        return (0);
    if (s1 == NULL || s2 == NULL)
        return (-1);
    while (*s1 && *s2)
    {
        if (*s1 >= 'a' && *s2 >= 'a')
        {
            if (*s1 != *s2)
                return (*s1 - *s2);
        }
        else if (*s1 >= 'A' && *s1 <= 'Z' && *s2 >= 'A' && *s2 <= 'Z')
        {
            if (*s1 != *s2)
                return (*s1 - *s2);
        }
        else if (*s1 >= 'a' && *s1 <= 'z' && *s2 >= 'A' && *s2 <= 'Z')
        {
            if (*s1 - 32 != *s2)
                return (*s1 - 32 - *s2);
        }
        else if (*s1 >= 'A' && *s1 <= 'Z' && *s2 >= 'a' && *s2 <= 'z')
        {
            if (*s1 + 32 != *s2)
                return (*s1 + 32 - *s2);
        }
        else
        {
            if (*s1 != *s2)
                return (*s1 - *s2);
        }
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int ft_strncoll(const char *s1, const char *s2, size_t n)
{
    if (s1 == NULL && s2 == NULL)
        return (0);
    if (s1 == NULL || s2 == NULL)
        return (-1);
    while (*s1 && *s2 && n > 0)
    {
        if (*s1 >= 'a' && *s2 >= 'a')
        {
            if (*s1 != *s2)
                return (*s1 - *s2);
        }
        else if (*s1 >= 'A' && *s1 <= 'Z' && *s2 >= 'A' && *s2 <= 'Z')
        {
            if (*s1 != *s2)
                return (*s1 - *s2);
        }
        else if (*s1 >= 'a' && *s1 <= 'z' && *s2 >= 'A' && *s2 <= 'Z')
        {
            if (*s1 - 32 != *s2)
                return (*s1 - 32 - *s2);
        }
        else if (*s1 >= 'A' && *s1 <= 'Z' && *s2 >= 'a' && *s2 <= 'z')
        {
            if (*s1 + 32 != *s2)
                return (*s1 + 32 - *s2);
        }
        else
        {
            if (*s1 != *s2)
                return (*s1 - *s2);
        }
        s1++;
        s2++;
        n--;
    }
    return (*s1 - *s2);
}
