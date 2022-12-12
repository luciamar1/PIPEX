#include "get_next_line.h"

void	ft_lstadd_back(t_list **lst, void *content)
{
	t_list	*last;
	t_list	*new;

	new = (void *)malloc(sizeof(t_list));
	new->content = content;
	new->next = NULL;
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	if (last == NULL)
		return ;
	while (last->next != NULL)
		last = last -> next;
	last -> next = new;
}

void	ft_lstiter(t_list *ls, size_t (*ft_len)(const char *)
, char *ft_p, char	**s, int *l)
{
	char	*cont;

	while (ls)
	{
		if (ft_p == NULL)
		{
			*l += ft_len(ls->content);
		}
		if (ft_len == NULL)
		{
			cont = (char *) ls->content;
			while (*cont)
			{
				*(*s) = *(cont++);
				(*s)++;
			}
		}
		ls = ls->next;
	}
}

void	iterador(char **st, char **s, int *i)
{
	int	e;
	int	x;

	x = 0;
	e = 0;
	while ((*s)[*i])
	{
		if ((*s)[*i] == '\n')
		{
			x = *i + 1;
			*st = ft_calloc(ft_strlen(&(s[0][*i])), 1);
			while ((*s)[++(*i)])
				(*st)[e++] = (*s)[*i];
			(*s)[x] = 0;
			*i = x - 1;
			break ;
		}
		*i = *i + 1;
	}			
}

char	*ft_copy(char *str)
{
	char		*ret;
	int			counter;

	ret = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!ret)
		return (NULL);
	counter = 0;
	while (str[counter])
	{
		ret[counter] = str[counter];
		counter ++;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	char			*s;
	static char		*st;
	t_list			*ls;
	int				i;
	int				x;

	s = ((i = ((ls = NULL), 0)), ft_calloc(BUFFER_SIZE + 1, 1));
	while (s[i] != '\n')
	{
		ft_bzero((i = 0, s), BUFFER_SIZE + 1);
		if (st)
			st = ((s = (free(s), ft_copy(st))), free(st), NULL);
		else
			if (read(fd, s, BUFFER_SIZE) <= 0)
				break ;
		ft_lstadd_back((iterador(&st, &s, &i), &ls), ft_strdup(s));
	}
	if (ls == NULL)
		return (free(s), ft_freelist(ls), free(st), NULL);
	ft_lstiter((x = (free(s), 0), ls), &ft_strlen, NULL, NULL, &x);
	ft_lstiter((s = ft_calloc(x + 1, 1), ls), NULL, "ft_put", &s, NULL);
	if (ft_freelist(ls), !*(s - x))
		return (free(s - x), NULL);
	return (s - x);
}

