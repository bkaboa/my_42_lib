#ifndef LIBFT_H
# define LIBFT_H

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

#include <stdbool.h>

# define BASE_10 "0123456789"
# define BASE_16 "0123456789abcdef"

// ft_is.c
bool    ft_isnumber(const char *str);
bool    ft_isdecimal(const char *str);
bool    ft_ishex(const char *str);
bool    ft_isdigit(const int c);
bool    ft_isalpha(const int c);
bool    ft_isalnum(const int c);
bool    ft_isascii(const int c);
bool    ft_isprint(const int c);
bool    ft_isspace(const int c);
bool    ft_islower(const int c);
bool    ft_isupper(const int c);
bool    ft_isblank(const int c);
bool    ft_iscntrl(const int c);
bool    ft_isgraph(const int c);
bool    ft_ispunct(const int c);

/* -------------------------------- */

// STRINGS FUNCTIONS

// ft_strcpy.c
int ft_strncpy(char *dest, const char *src, size_t n);

// ft_strcmp.c
int ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strcoll(const char *s1, const char *s2);
int ft_strncoll(const char *s1, const char *s2, size_t n);
int ft_strlowercasecmp(const char *s1, const char *s2);
int ft_struppercasecmp(const char *s1, const char *s2);
int ft_strloweralphanumcmp(const char *s1, const char *s2);

// ft_strcat.c
int ft_strcat(char *dest, const char *src);
int ft_strncat(char *dest, const char *src, size_t n);

// ft_strdup.c
int ft_strdup(char **dest, const char *src);
int ft_strndup(char **dest, const char *src, size_t n);

// ft_srejoin.c
char *ft_strjoin(const char *str1, const char *str2);

// ft_strlen.c
size_t ft_strlen(const char *str);

// ft_numlen.c
size_t ft_numlen(ssize_t n);
size_t ft_numlen_base(ssize_t n, size_t base);

// ft_strchr.c
char *ft_strchr(const char *s, int c);

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

/* -------------------------------- */

// NUMBERS FUNCTIONS

// ft_atoi.c
int ft_atoi(const char *str);
long ft_atol(const char *str);
int ft_atoi_base(const char *str, int base);

// ft_itoa.c
char *ft_itoa(const int n);
char *ft_itoa_base(const int n, const char *base);
char *ft_ultoa_base(const size_t n, const char *base);
char *ft_ultoa(const size_t n);
char *ft_ltoa(const ssize_t n);
char *ft_ltoa_base(const ssize_t n, const char *base);

/* -------------------------------- */

// NETWORK FUNCTIONS

// ntoh.c
u_int64_t ntohst(const u_int64_t data);

// hton.c
u_int64_t htonst(const u_int64_t data);

#endif