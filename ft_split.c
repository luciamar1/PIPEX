# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int    ft_to_find(char *large, char *small)
{
    int i;

    i = 2;
    while(i--)
    {
        if (*large != *small)
            return(0);
        large ++;
        small ++;
    }
    return (1);
}

char    *mallocseg(char *m, char *s, char *c)
{
        int     i;

        i = 0;
        while (s[i] && ft_to_find(s, c) == 0)
                i++;
        m = (char *)malloc((i + 1) * sizeof(char));
        if (!m)
                return (NULL);
        m[i] = 0;
        return (m);
}
 
char    *pon(char **s, char *c, char *m)
{
        int     n;

        n = 0;
        if (m == 0)
                return (m);
        while (**s && ft_to_find(*s, c) == 0)
        {
                m[n ++] = **s;
                (*s)++;
        }
        return (m);
}

int     pridimensioncount(char *s, char *c)
{
        int     p;

        p = 1;
        if (ft_to_find(s, c) == 1)
                p--;
        if (!*s)
                return (0);
        while (*s)
        {
                if ((ft_to_find(s, c) == 1/* && *(s + 1) != c) */ && *(s + 2) != '\0'))
                        p ++;
                s++;
        }
        return (p);
}

void    m_free(char **m, int i, int p)
{
        while (i - p++)
                free(*(--m));
        free(m);
}

char    **ft_split(char *s, char *c)
{
        char    **m;
        int             p;
        int             i;

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
                while (*s && ft_to_find(s, c) == 1)
                        s++;
                *m = pon(&s, c, mallocseg(*m, (char *)s, c));
                if (!*m)
                        m_free(m, i, p);
                m++;
        }
        return (m - i);
}

int     ft_strlen(char *s)
{
        int     l;
        
        l = 0;
        while(s[l])
                l++;
        return(l);
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

char    *ft_find_path(char **large, char *small)
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

int main(int argc, char **argv, char **envp)
{

    char **path;

    char *s = ":/";

    path = (ft_split(ft_find_path(envp,  "PATH"), s));
    while (*path)
    {
        printf("%s\n", *path);
        path++;
    }
    return (0);
}