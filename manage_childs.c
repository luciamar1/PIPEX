/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:00:19 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/03/01 12:46:34 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	first_child(t_tlist *pipex, int *file, char **argv)
{
	int	hd[2];

	if (pipex->heredoc == 0)
	{
		pipe(hd);
		ft_heredoc(&hd[1], argv[2]);
		if (dup2(hd[0], STDIN_FILENO) < 0)
		{
			ft_freecharmatrix(pipex->paths);
			ft_freeintmatrix(pipex->fd, pipex->ncomand);
			return (0);
		}
		close(hd[1]);
		close(hd[0]);
	}
	else
	{
		file[0] = open(argv[1], O_RDONLY);
		if (file[0] < 0)
		{
			ft_freecharmatrix(pipex->paths);
			ft_freeintmatrix(pipex->fd, pipex->ncomand);
			return (0);
		}	
		if (file[0] < 0)
		{
			ft_freecharmatrix(pipex->paths);
			ft_freeintmatrix(pipex->fd, pipex->ncomand);
			return (0);
		}	
		if (dup2(file[0], STDIN_FILENO) < 0)
		{
			ft_freecharmatrix(pipex->paths);
			ft_freeintmatrix(pipex->fd, pipex->ncomand);
			return (0);
		}	
	}
	if (dup2 (pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
	{
		ft_freecharmatrix(pipex->paths);
		ft_freeintmatrix(pipex->fd, pipex->ncomand);
		return (0);
	}
	return (0);
}

int	middle_child(t_tlist *pipex)
{
	if (dup2(pipex->fd[pipex->comand - 1][0], STDIN_FILENO) < 0)
	{
		ft_freecharmatrix(pipex->paths);
		ft_freeintmatrix(pipex->fd, pipex->ncomand);
		return (0);
	}
	if (dup2 (pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
	{
		ft_freecharmatrix(pipex->paths);
		ft_freeintmatrix(pipex->fd, pipex->ncomand);
		return (0);
	}
	return (0);
}

int	final_child(t_tlist *pipex, int *file, char **argv, int argc)
{
	if (pipex->heredoc == 0 && pipex->comand == argc - 5)
		file[1] = open(argv[argc - 1], O_WRONLY | O_APPEND, 0666);
	if (pipex->pid == 0 && (pipex->comand == argc - 4))
		file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file[1] < 0)
	{
		ft_freecharmatrix(pipex->paths);
		ft_freeintmatrix(pipex->fd, pipex->ncomand);
		return (0);
	}
	if (dup2(file[1], STDOUT_FILENO) < 0)
	{
		ft_freecharmatrix(pipex->paths);
		ft_freeintmatrix(pipex->fd, pipex->ncomand);
		return (0);
	}
	if (dup2(pipex->fd[pipex->comand - 1][0], STDIN_FILENO) < 0)
	{
		ft_freecharmatrix(pipex->paths);
		ft_freeintmatrix(pipex->fd, pipex->ncomand);
		return (0);
	}
	return (0);
}

void	ft_place_comand(t_tlist *pipex, int argc, char **argv, char **envp)
{
	int	file[2];	
	if (pipex->comand == 0)
		first_child(pipex, file, argv);
	else if ((pipex->comand != argc - 4 && pipex->heredoc != 0) || \
	(pipex->comand != argc - 5 && pipex->heredoc == 0))
	{
		printf("me meto?\n");
		middle_child(pipex);
	}
	if ((pipex->comand == argc - 4 || (pipex->heredoc == 0 \
	&& pipex->comand == argc - 5)))
		final_child(pipex, file, argv, argc);
	ft_execute(pipex, argv, envp);
}
