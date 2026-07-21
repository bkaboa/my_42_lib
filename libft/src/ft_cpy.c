#include "libft.h"

int	ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t			i;
	size_t			words;
	size_t			*dest_words;
	const size_t	*src_words;
    bool            is_aligned = false;

	if (dest == NULL || src == NULL)
		return (-1);
	i = 0;
	/* Align both pointers on sizeof(size_t) with byte copies. */
	while (i < n && !is_aligned)
	{
		dest[i] = src[i];
		i++;
        if ((((size_t)(dest + i) | (size_t)(src + i)) & (sizeof(size_t) - 1)) == 0) {
            is_aligned = true;
            break;
        }
	}
	/* Bulk copy by machine words only when both are aligned. */
	if (is_aligned) {
	    words = (n - i) / sizeof(size_t);
	    dest_words = (size_t *)(dest + i);
	    src_words = (const size_t *)(src + i);
	    while (words > 0)
	    {
	    	*dest_words = *src_words;
	    	dest_words++;
	    	src_words++;
	    	words--;
	    }
	    i += ((n - i) / sizeof(size_t)) * sizeof(size_t);
    }
	/* Remaining bytes. */
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return ((int)n);
}
