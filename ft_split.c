# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
//# include "libft.h"
# include "pipex.h"


char	*ft_strjoinpip(char const *s1, char const *s2)
{
	char	*s;
	int		l;

	// printf("s1 === %s\n", s1);
	// printf("s2 === %s\n", s1);
	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = malloc(l * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);	
	while (*s1)
		*s++ = *s1++;
	*s++ = 47;
	while (*s2)
		*s++ = *s2++;
	*s = 0;
	return (s - l);
}

char	*mallocseg(char *m, char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	m = (char *)malloc((i + 1) * sizeof(char));
	if (!m)
		return (NULL);
	m[i] = 0;
	return (m);
}

char	*pon(char **s, char c, char *m)
{
	int	n;

	n = 0;
	if (m == 0)
		return (m);
	while (**s && **s != c)
	{
		m[n ++] = **s;
		(*s)++;
	}
	return (m);
}

int	pridimensioncount(char const *s, char c)
{
	int	p;

	p = 1;
	if (*s == c)
		p--;
	if (!*s)
		return (0);
	while (*s)
	{
		if ((*s == c && *(s + 1) != c) && *(s + 1) != '\0')
			p ++;
		s++;
	}
	return (p);
}

void	m_free(char **m, int i, int p)
{
	while (i - p++)
		free(*(--m));
	free(m);
}

char	**ft_splitpip(char *s, char c)
{
	char	**m;
	int		p;
	int		i;

	if (!s)
		return (NULL);
	else
		p = pridimensioncount(s, c);
	m = malloc((p + 1) * sizeof(char *));
	if (!m)
		return (NULL);
	i = p;
	m[p] = NULL;
	while (p--)
	{
		while (*s && *s == c)
			s++;
		*m = pon(&s, c, mallocseg(*m, (char *)s, c));
		if (!*m)
			m_free(m, i, p);
		m++;
	}
	return (m - i);
}




int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
        if (n == 0)
                return (0);
        while (*s1 && *s2 && *s1 == *s2 && --n)
        {
                s1 ++;
                s2 ++;
        }
        return ((unsigned char)*s1 - (unsigned char)*s2);
}

char    *ft_find_paths(char **large, char *small)
{
        size_t  lsmall;
        size_t  i;

        i = 0;
        lsmall= ft_strlen(small);
        while (*large)
        {
                if (!ft_strncmp(*large, small, lsmall))
                        return (*large);
                large++;
        }
        return (NULL);
}

// int main(int argc, char **argv, char **envp)
// {

//     char **path;

//     char *s = ":/";

//     path = (ft_split(ft_find_paths(envp,  "PATH"), ':'));
//     *path += 5;
//     while (*path)
//     {
//         printf("%s\n", *path);
//         path++;
//     }
//     return (0);
// }