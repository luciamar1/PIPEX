/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:00:43 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/02/27 14:32:33 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

void	leaks(void)
{
	system("leaks -q pipex");
}

int	main(int argc, char **argv, char **envp)
{
	t_tlist	pipex;
	int		file;

	pipex.heredoc = ft_strncmp("here_doc", argv[1], 9);
	file = open(argv[1], O_RDONLY);
	if (pipex.heredoc != 0 && file < 0)
		return (0);
	pipex.comand = 0;
	pipex.ncomand = argc - 3;
	if (pipex.heredoc == 0)
		pipex.ncomand = argc - 4;
	pipex.paths = (ft_split(ft_find_paths(envp, "PATH"), ':'));
	*pipex.paths = *pipex.paths + 5;
	ft_create_childs_fd(&pipex);
	if (pipex.pid == 0)
		ft_place_comand(&pipex, argc, argv, envp);
	while (pipex.ncomand --)
		wait(NULL);
	ft_freeintmatrix(pipex.fd, pipex.ncomand);
	ft_freecharmatrix(pipex.paths);
	atexit(leaks);
	return (0);
}
