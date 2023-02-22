/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:51:04 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/02/15 17:06:46 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <errno.h>

int	first_child(t_dllist *pipex, int *file, char **argv)
{
	int	hd[2];

	if (pipex->heredoc == 0)
	{
		pipe(hd);
		ft_heredoc(&hd[1], argv[2]);
		if (dup2(hd[0], STDIN_FILENO) < 0)
			return (0);
		close(hd[1]);
		close(hd[0]);
	}
	else
	{
		if ((file[0] = open(argv[1], O_RDONLY)) < 0)
			return (0);
		if (file[0] < 0)
			return (0);
		if (dup2(file[0], STDIN_FILENO) < 0)
			return (0);
	}
	if (dup2 (pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
		return (0);
	return (0);
}

int	middle_child(t_dllist *pipex)
{
	
		if (dup2(pipex->fd[pipex->comand - 1][0], STDIN_FILENO) < 0)
			return (0);
		if (dup2 (pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
			return (0);
	return (0);
}

int	final_child(t_dllist *pipex, int *file, char **argv, int argc)
{
	if ((file[1] = open(argv[argc - 1], O_WRONLY \
	| O_CREAT | O_TRUNC, 0666)) < 0)
		return (0);
	if (dup2(file[1], STDOUT_FILENO) < 0)
		return (0);
	if (dup2(pipex->fd[pipex->comand - 1][0], STDIN_FILENO) < 0)
		return (0);
	return (0);
}

void	ft_place_comand(t_dllist *pipex, int argc, char **argv, char **envp)
{
	int	file[2];

	if (pipex->comand == 0)
		first_child(pipex, file, argv);
	if ((pipex->comand != argc - 4 && (pipex->heredoc != 0) \
	&& pipex->comand != 0))
		middle_child(pipex);
	if ((pipex->comand == argc - 4 || (pipex->heredoc == 0 \
	&& pipex->comand == argc - 5)))
		final_child(pipex, file, argv, argc);
	ft_execute(pipex, argv, envp);
}

int main(int argc, char **argv, char **envp)
{
	t_dllist	pipex;
	int			file[2];

	if ((file[0] = open(argv[1], O_RDONLY)) < 0)
		return (0);
	pipex.heredoc = ft_strncmp("here_doc", argv[1], 9);
	pipex.comand = 0;
	pipex.ncomand = argc - 3;
	if (pipex.heredoc == 0)
		pipex.ncomand = argc - 4;
	pipex.paths = (ft_split(ft_find_paths(envp,  "PATH"), ':'));
	*pipex.paths = *pipex.paths + 5;
	ft_create_childs_fd(&pipex);
	if (pipex.pid == 0)
		ft_place_comand(&pipex, argc, argv, envp);
	while (pipex.ncomand --)
		wait(NULL);
	return (0);
}