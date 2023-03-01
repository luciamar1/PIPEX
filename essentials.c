/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:00:16 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/02/28 19:28:25 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

void	ft_heredoc(int *file, char *delimitador)
{
	char	*gnl;
	int		i;

	while (1)
	{
		i = 0;
		gnl = get_next_line(STDIN_FILENO);
		if (ft_strncmp(gnl, delimitador, ft_strlen(delimitador)) == 0)
			break ;
		while (gnl[i])
			write(*file, &gnl[i++], 1);
		free (gnl);
	}	
}

int	ft_execute(t_tlist *pipex, char **argv, char **envp)
{
	char	**comando;
	int		i;

	i = 0;
	if (pipex->heredoc == 0)
		comando = ft_split(argv[pipex->comand + 3], ' ');
	else
		comando = ft_split(argv[pipex->comand + 2], ' ');
	while (pipex->paths[i])
	{
		pipex->paths[i] = ft_strjoinpip(pipex->paths[i], comando[0]);
		dprintf(STDERR_FILENO, "wattaaaaaaafaaaaac =) %s\n", pipex->paths[i]);
		if (access(pipex->paths[i], X_OK) != -1)
			break ;
		i ++;
	}
	ft_freeintmatrix(pipex->fd, pipex->ncomand);
	execve(pipex->paths[i], comando, envp);
	ft_freecharmatrix(pipex->paths);
	ft_freecharmatrix(comando);
	return (0);
}

int	ft_create_pipe(t_tlist *pipex)
{
	int	ncomand;
	int	counter;

	ncomand = pipex->ncomand;
	counter = 0;
	pipex->fd = malloc(ncomand * sizeof(int *));
	if (pipex->fd == NULL)
	{
		ft_freecharmatrix(pipex->paths);
		return (0);
	}
	while (ncomand)
	{
		pipex->fd[counter] = malloc(2 * sizeof(int));
		if (pipex->fd[counter] == NULL)
		{
			ft_freecharmatrix(pipex->paths);
			return (0);
		}
		pipe(pipex->fd[counter]);
		ncomand --;
		counter++;
	}
	return (0);
}

int	ft_create_childs_fd(t_tlist *pipex)
{
	ft_create_pipe(pipex);
	while (pipex->comand < pipex->ncomand)
	{
		pipex->pid = fork();
		if (pipex->comand != 0)
			close(pipex->fd[pipex->comand - 1][1]);
		if (pipex->pid == 0)
			break ;
		if (pipex->pid < 0)
			return (0);
		pipex->comand ++;
	}
	return (1);
}
