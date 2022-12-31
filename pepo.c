#include "pipex.h"
#include "libft/libft.h"

#include <fcntl.h>
#include <errno.h>

void	ft_heredoc(int *file, char *delimitador)
{
	char *gnl;
	
	while(1)
	{
		gnl = get_next_line(STDIN_FILENO);
		if (ft_strncmp(gnl, delimitador, ft_strlen(delimitador)) == 0)
			break;
		while (*gnl)
			write(*file, gnl++, 1);
	}	
}

//format()
// void    ifchild(int *comand)
void    *ft_malloc(int ncomand, int **fd)
{
    int i;

    i = 0;
    fd = malloc((ncomand) * sizeof(int *));
    if (fd == NULL)
        return(NULL);
    while (ncomand--)
    {
        fd[i++] = malloc(2 * sizeof(int));
        if (fd[i - 1] == NULL)
            return(NULL);
    }
    return(fd);
}
int    first_child(int file, int comand, int heredoc, char **argv, int **fd)
{
    if(heredoc == 0)
	{
		int fdheredoc[2];

		pipe(fdheredoc);
		ft_heredoc(&fdheredoc[1], argv[2]);
		if (dup2(fdheredoc[0], STDIN_FILENO) < 0)
		    return(0);
		close(fdheredoc[1]);	
		close(fdheredoc[0]);
	}

    else
		{
			file = open(argv[1], O_RDONLY);
			if(file < 0)
				return(0);
			if (dup2(file, STDIN_FILENO) < 0)
				return(0);
		}
		if (dup2(fd[comand][1], STDOUT_FILENO) < 0)
			return(0);
        return(1);
}

int    middle_child(int command, int **fd)
{
    if (dup2(fd[command - 1][0], STDIN_FILENO) < 0)
 			return(0);
	if (dup2( fd[command][1], STDOUT_FILENO) < 0)
		return(0);
	close(fd[command][0]);
	close(fd[command][1]);
    return(1);
}

int    final_child(int file, int command, char **argv, int **fd, int argc)
{
    file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(file < 0)
    	return(0);
    if (dup2(file, STDOUT_FILENO) < 0)
    	return(0);
    if (dup2(fd[command - 1][0], STDIN_FILENO) < 0)
    	return(0);
    close(fd[command][0]);
    close(fd[command][1]);
    return(1);
}

void    ft_execute(char **argv, int comand, char **paths, char **envp)
{
    char **comando;
    int i;

    i = 0;
	comando = ft_splitpip(argv[comand + 1], ' ');
    while(paths[i])
    {
    	paths[i] = ft_strjoinpip(paths[i], comando[0]);
    	if(access(paths[i], X_OK) != -1)
    		break;
    	i ++;
    }
    execve(paths[i], comando, envp);
}

void ifpid(tt_list pipex, int argc, char **argv, char **envp)
{
    int file[2];

    if(pipex.comand == 0)
        first_child(file[0], pipex.comand, pipex.heredoc, argv, pipex.fd);
    if(pipex.pid == 0 && (pipex.comand != argc - 4 && (pipex.heredoc != 0) && pipex.comand != 0))
        middle_child(pipex.comand, pipex.fd);
    if (pipex.pid == 0 && (pipex.comand == argc - 4 || (pipex.heredoc == 0 && pipex.comand == argc - 5)))
        final_child(file[1], pipex.comand, argv, pipex.fd, argc);
    if (pipex.pid == 0)
        ft_execute(argv, pipex.comand, pipex.paths, envp);
}

void    creationchilds(tt_list *pipex, int argc, char **argv, char **envp)
{
   int x;
   int i;
   
   i = 0;
   x = pipex->ncomand;
   while(x--)
        pipe(pipex->fd[i++]);
    x = 2;
    i = 0;
    while(x--)
        dprintf(STDERR_FILENO, "caracola en vinagre %d\n", (pipex->fd[i++][0]));
    dprintf(STDERR_FILENO, "hola %d\n", x);

    while(pipex->comand < pipex->ncomand)
    {
    pipex->pid = fork();
        if(pipex->pid == 0)
        {
            dprintf(STDERR_FILENO, "%d\n", pipex->comand);
            break;
        }
        if(pipex->pid < 0)
            exit(0);
        (pipex->comand)++;
    }
    ifpid(*pipex, argc, argv, envp);
}

int main(int argc, char **argv, char **envp)
{
    tt_list pipex;
    // int pipex.heredoc;
    // int ncomand;
    // int comand;
    // int pid;

    //heredoc si == 0
    pipex.comand = 0;
    pipex.heredoc = ft_strncmp("here_doc", argv[1], 9);
    pipex.ncomand = argc - 3;
    if((pipex.fd = malloc((argc - 3) * sizeof(int *))))  
        return(NULL);

    dprintf(STDERR_FILENO, "jnjnjjn%d\n", pipex.comand);
    if(*(pipex.fd) = malloc(2*sizeof(int)))
        return(NULL);
    pipex.paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
    *(pipex.paths) += 5;
    if (pipex.heredoc == 0)
        pipex.ncomand = argc - 4;
    if (argc < 5 || (pipex.heredoc == 0 && argc < 6))
		return(0);
    creationchilds(&pipex, argc, argv, envp);
    while(pipex.ncomand --)
        wait(NULL);
    return(0);
}