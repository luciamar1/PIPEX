#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <errno.h>

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

int	ft_execute(tt_list *pipex, char **argv, char **envp)
{
	char	**comando;
	int		i;

	i = 0;
	comando = ft_splitpip(argv[pipex->comand + 2], ' ');
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

int	first_child(tt_list *pipex, int *file, char **argv)
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

int	middle_child(tt_list *pipex, int argc)
{
	if (pipex->pid == 0 && (pipex->comand != argc - 4 \
	&& (pipex->heredoc != 0) && pipex->comand != 0))
	{
		if (dup2(pipex->fd[pipex->comand - 1][0], STDIN_FILENO) < 0)
			return (0);
		if (dup2 (pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
			return (0);
	}
	return (0);
}

int	final_child(tt_list *pipex, int *file, char **argv, int argc)
{
	if (pipex->pid == 0 && (pipex->comand == argc - 4 \
	|| (pipex->heredoc == 0 && pipex->comand == argc - 5)))
	{
		if ((file[1] = open(argv[argc - 1], O_WRONLY \
		| O_CREAT | O_TRUNC, 0666)) < 0)
			return (0);
		if (dup2(file[1], STDOUT_FILENO) < 0)
			return (0);
		if (dup2(pipex->fd[pipex->comand-1][0], STDIN_FILENO) < 0)
			return (0);
	}
	return (0);
}

void ft_place_comand(tt_list *pipex, int argc, char **argv, char **envp)
{
	int	file[2];

	if (pipex->comand == 0)
		first_child(pipex, file, argv);
	if ((pipex->comand != argc - 4 && (pipex->heredoc != 0) \
	&& pipex->comand != 0))
		middle_child(pipex, argc);
	if ((pipex->comand == argc - 4 || (pipex->heredoc == 0 \
	&& pipex->comand == argc - 5)))
		final_child(pipex, file, argv, argc);
	ft_execute(pipex, argv, envp);
}

int	ft_create_pipe(tt_list *pipex)
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

int	ft_create_childs_fd(tt_list *pipex)
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

int main(int argc, char **argv, char **envp)
{
	tt_list	pipex;

	pipex.heredoc = ft_strncmp("here_doc", argv[1], 9);
	pipex.heredoc = argc - 3; 
	pipex.comand = 0;
	pipex.ncomand = argc - 3;
	if (pipex.heredoc == 0)
		pipex.ncomand = argc - 4;
	pipex.paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
	*pipex.paths = *pipex.paths + 5;
	ft_create_childs_fd(&pipex);
	if (pipex.pid == 0)
		ft_place_comand(&pipex, argc, argv, envp);
	while (pipex.ncomand --)
		wait(NULL);
	return (0);
}