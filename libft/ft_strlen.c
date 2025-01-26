#include "libft.h"

size_t ft_strlen(const char *str)
{
    const u_int64_t *longword_ptr;
    u_int64_t longword, himagic, lomagic;

    longword_ptr = (u_int64_t *)str;

    if (str == NULL)
        return (0);
    while (1)
    {
        longword = *longword_ptr++;

        if (((longword - 0x0101010101010101L) & ~longword & 0x8080808080808080L) != 0)
        {
            const char *cp = (const char *)(longword_ptr - 1);

            if (cp[0] == 0)
                return cp - str;
            if (cp[1] == 0)
                return cp - str + 1;
            if (cp[2] == 0)
                return cp - str + 2;
            if (cp[3] == 0)
                return cp - str + 3;
            if (cp[4] == 0)
                return cp - str + 4;
            if (cp[5] == 0)
                return cp - str + 5;
            if (cp[6] == 0)
                return cp - str + 6;
            if (cp[7] == 0)
                return cp - str + 7;
        }
    }
}