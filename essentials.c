/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:00:16 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/03/01 19:58:27 by lucia-ma         ###   ########.fr       */
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
	int		counter;

	counter = 0;
	while (1)
	{
		gnl = get_next_line(STDIN_FILENO);
		if (ft_strncmp(gnl, delimitador, ft_strlen(delimitador)) == 0)
			break ;
		while (gnl[counter])
			write(*file, &gnl[counter++], 1);
		free (gnl);
	}	
}

int	verify_access(t_tlist *pipex, char **comando, int *i)
{
	while (pipex->paths[*i])
	{
		pipex->paths[*i] = ft_strjoinpip(pipex->paths[*i], comando[0]);
		if (pipex->paths[*i] == NULL)
		{
			ft_freecharmatrix(comando);
			ft_freepathfdncomand(pipex, pipex->ncomand);
			return (-1);
		}
		if (access(pipex->paths[*i], X_OK) != -1)
			return (1);
		(*i)++;
	}
	return (-1);
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
	if (!comando)
	{
		ft_freepathfdncomand(pipex, pipex->ncomand);
		return (0);
	}
	if (verify_access(pipex, comando, &i) == 1)
	{
		ft_freeintmatrix(pipex->fd, pipex->ncomand);
		execve(pipex->paths[i], comando, envp);
	}
	else
		ft_freeintmatrix(pipex->fd, pipex->ncomand);
	exit(1);
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
		if (pipex->fd[counter] == NULL || pipe(pipex->fd[counter]) < 0)
		{
			ft_freepathfdncomand(pipex, counter + 1);
			return (0);
		}
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
		{
			ft_freecharmatrix(pipex->paths);
			return (0);
		}
		pipex->comand ++;
	}
	return (1);
}
