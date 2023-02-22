/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hijos_y_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:47:14 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/02/15 14:56:56 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <unistd.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include "pipex.h"

int	ft_create_childs_fd(t_dllist *pipex)
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

int	ft_create_pipe(t_dllist *pipex)
{
	int	ncomand;
	int	counter;

	ncomand = pipex->ncomand;
	counter = 0;
	pipex->fd = malloc(ncomand * sizeof(int *));
	if (pipex->fd == NULL)
		return (0);
	while (ncomand)
	{
		pipex->fd[counter] = malloc(2 * sizeof(int));
		if (pipex->fd[counter] == NULL)
			return (0);
		pipe(pipex->fd[counter]);
		ncomand --;
	}
	return (0);
}
