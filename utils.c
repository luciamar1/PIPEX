/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:47:37 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/02/15 14:54:38 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <unistd.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include "pipex.h"

void	ft_heredoc(int *file, char *delimitador)
{
	char	*gnl;

	while (1)
	{
		gnl = get_next_line(STDIN_FILENO);
		if (ft_strncmp(gnl, delimitador, ft_strlen(delimitador)) == 0)
			break ;
		while (*gnl)
			write(*file, gnl++, 1);
	}	
}

int	ft_execute(t_dllist *pipex, char **argv, char **envp)
{
	char	**comando;
	int		i;

	i = 0;
	comando = ft_split(argv[pipex->comand + 2], ' ');
	if (pipex->heredoc == 0)
		comando = ft_split(argv[pipex->comand + 3], ' ');
	while (pipex->paths[i])
	{
		pipex->paths[i] = ft_strjoinpip(pipex->paths[i], comando[0]);
		if (access(pipex->paths[i], X_OK) != -1)
		{
			break ;
		}
		i ++;
	}
	execve(pipex->paths[i], comando, envp);
	return (0);
}

char	*ft_strjoinpip(char const *s1, char const *s2)
{
	char	*s;
	int		l;

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

char	*ft_find_paths(char **large, char *small)
{
	size_t	lsmall;

	lsmall = ft_strlen(small);
	while (*large)
	{
		if (!ft_strncmp(*large, small, lsmall))
			return (*large);
		large++;
	}
	return (NULL);
}
