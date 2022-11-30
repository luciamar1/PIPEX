#ifndef PIPEX_H
# define PIPEX_H

# include <stdarg.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

char    *ft_find_path(char **large, char *small);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char    **ft_split(char *s, char *c);
int ft_putnbr(int n);
int	ft_putchar(char c);
int	ft_putstr(const char *s);
int	ft_putnbr_base(int nb, char *base);
int	ft_putptr_base(unsigned long long nb, char *base, char p);
int	ft_strlen(const char	*s);
int	ft_printf(char const *s, ...);
int	wall_happen(va_list *args, char happen);

#endif