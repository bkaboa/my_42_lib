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

int ft_strlowercasecmp(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL)
        return (0);
    if (s1 == NULL || s2 == NULL)
        return (-1);
    while (*s1 && *s2)
    {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? (*s1 + 32) : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? (*s2 + 32) : *s2;
        if (c1 != c2)
            return (c1 - c2);
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int ft_struppercasecmp(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL)
        return (0);
    if (s1 == NULL || s2 == NULL)
        return (-1);
    while (*s1 && *s2)
    {
        char c1 = (*s1 >= 'a' && *s1 <= 'z') ? (*s1 - 32) : *s1;
        char c2 = (*s2 >= 'a' && *s2 <= 'z') ? (*s2 - 32) : *s2;
        if (c1 != c2)
            return (c1 - c2);
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int ft_strloweralphanumcmp(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL)
        return (0);
    if (s1 == NULL || s2 == NULL)
        return (-1);
    while (*s1 && *s2)
    {
        if (!ft_isalnum(*s1))
        {
            s1++;
            continue;
        }
        if (!ft_isalnum(*s2))
        {
            s2++;
            continue;
        }
        char c1 = (*s1 >= 'a' && *s1 <= 'z') ? (*s1 - 32) : *s1;
        char c2 = (*s2 >= 'a' && *s2 <= 'z') ? (*s2 - 32) : *s2;
        if (c1 != c2)
            return (c1 - c2);
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}
