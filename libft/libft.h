#ifndef LIBFT_H
# define LIBFT_H

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdbool.h>

// ft_is.c
bool    ft_isnumber(const char *str);
bool    ft_isdecimal(const char *str);
bool    ft_ishex(const char *str);
bool    ft_isdigit(const char c);
bool    ft_isalpha(const char c);
bool    ft_isalnum(const char c);
bool    ft_isascii(const char c);
bool    ft_isprint(const char c);
bool    ft_isspace(const char c);
bool    ft_islower(const char c);
bool    ft_isupper(const char c);
bool    ft_isblank(const char c);
bool    ft_iscntrl(const char c);
bool    ft_isgraph(const char c);
bool    ft_ispunct(const char c);

/* -------------------------------- */

// STRINGS FUNCTIONS

// ft_strcmp.c
int ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strcoll(const char *s1, const char *s2);
int ft_strncoll(const char *s1, const char *s2, size_t n);

// ft_strcat.c
int ft_strcat(char *dest, const char *src);
int ft_strncat(char *dest, const char *src, size_t n);

// ft_strdup.c
int ft_strdup(char **dest, const char *src);

// ft_srejoin.c
char *ft_strjoin(const char *str1, const char *str2);

// ft_strlen.c
size_t ft_strlen(const char *str);

/* -------------------------------- */

// CONVERSION FUNCTIONS

//ft_to.c
int ft_strToupper(char *str);
int ft_strTolower(char *str);
int ft_tolower(int c);
int ft_toupper(int c);
int ft_toascii(int c);
int ft_tochar(int c);

/* -------------------------------- */

// MEMORY FUNCTIONS

// ft_memcmp.c
int ft_memcmp(const void *addr1, const void *addr2, size_t n);

// ft_memcpy.c
int ft_memcpy(void *dst, const void *src, size_t n);

// ft_memset.c
int ft_memset(void *addr, const u_int8_t c, size_t n);

// ft_realloc.c
int ft_realloc(void **ptr, size_t size);

/* -------------------------------- */

// SWAP FUNCTIONS

// ft_swap.c
void ft_swap(void *addr, void *addr2);

/* -------------------------------- */

// PRINT FUNCTIONS

// ft_putchar.c
void    ft_putchar(const char c);

// ft_putstr.c
void    ft_putstr(const char *str);

#endif