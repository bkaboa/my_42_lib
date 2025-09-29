# include "ft_gnl.h"

static t_gnl_list *get_fd_node(t_gnl_list **head, int fd)
{
    t_gnl_list *current = *head;
    while (current)
    {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    t_gnl_list *new_node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
    if (!new_node)
        return NULL;
    new_node->fd = fd;
    new_node->remainder = NULL;
    new_node->next = *head;
    *head = new_node;
    return new_node;
}

static void remove_fd_node(t_gnl_list **head, int fd)
{
    t_gnl_list *current = *head;
    t_gnl_list *prev = NULL;
    while (current)
    {
        if (current->fd == fd)
        {
            if (prev)
                prev->next = current->next;
            else
                *head = current->next;
            free(current->remainder);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int ft_gnl(int fd, char **line)
{
    static t_gnl_list *head = NULL;
    t_gnl_list *fd_node;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char *newline_pos;
    char *temp;

    if (fd < 0 || !line || BUFFER_SIZE <= 0)
        return -1;
    fd_node = get_fd_node(&head, fd);
    if (!fd_node)
        return -1;
    while (1)
    {
        if (fd_node->remainder && (newline_pos = ft_strchr(fd_node->remainder, '\n')))
        {
            ft_strndup(line, fd_node->remainder, newline_pos - fd_node->remainder + 1);
            ft_strndup(&temp, newline_pos + 1, BUFFER_SIZE);
            free(fd_node->remainder);
            fd_node->remainder = temp;
            return 1;
        }
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            remove_fd_node(&head, fd);
            return -1;
        }
        if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        if (fd_node->remainder == NULL)
        {
            if (ft_strdup(&temp, buffer) == -1)
            {
                remove_fd_node(&head, fd);
                return -1;
            }
        }
        else
        {
            temp = ft_strjoin(fd_node->remainder, buffer);
            if (temp == NULL)
            {
                remove_fd_node(&head, fd);
                return -1;
            }
        }
        free(fd_node->remainder);
        fd_node->remainder = temp;
    }
    if (fd_node->remainder)
    {
        *line = fd_node->remainder;
        fd_node->remainder = NULL;
        remove_fd_node(&head, fd);
        return 0;
    }
    *line = NULL;
    remove_fd_node(&head, fd);
    return 0;
}