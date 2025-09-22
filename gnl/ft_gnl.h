#ifndef FT_GNL_H
# define FT_GNL_H

# include "logger/ft_logger.h"
# include "libft/libft.h"

# define BUFFER_SIZE 42

typedef struct      s_gnl_list
{
    int             fd;
    char            *remainder;
    struct s_gnl_list *next;
}                   t_gnl_list;

int ft_gnl(int fd, char **line);

#endif