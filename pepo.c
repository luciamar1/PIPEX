#include "pipex.h"
#include "libft/libft.h"

#include <fcntl.h>
#include <errno.h>

void    ft_close_all(tt_list *pipex)
{
    int counter;
    counter = pipex->ncomand;
    while(counter-- <= pipex->ncomand)
    {
        close(pipex->fd[counter][0]);
        close(pipex->fd[counter][1]);
    }
}
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
int    first_child(tt_list *pipex, int *file, char **argv)
{
    if(pipex->heredoc == 0)
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
	    *file = open(argv[1], O_RDONLY);
        if(*file < 0)
            return(0);
        if (dup2(*file, STDIN_FILENO) < 0)
        	return(0);
	}
	if (dup2(pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
			return(0);
    dprintf(STDERR_FILENO, "oosjdpsojdsopja\n");
    return(1);
}

int    middle_child(tt_list *pipex)
{
    if (dup2(pipex->fd[pipex->comand - 1][0], STDIN_FILENO) < 0)
 			return(0);
	if (dup2( pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
		return(0);
	close(pipex->fd[pipex->comand][0]);
	close(pipex->fd[pipex->comand][1]);
    return(1);
}

int    final_child(tt_list *pipex, int *file, char **argv, int argc)
{
    *file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(*file < 0)
    	return(0);
    if (dup2(*file, STDOUT_FILENO) < 0)
    	return(0);
    if (dup2(pipex->fd[(pipex->comand) - 1][0], STDIN_FILENO) < 0)
    	return(0);
    close(pipex->fd[pipex->comand][0]);
    close(pipex->fd[pipex->comand][1]);
    close(pipex->fd[(pipex->comand) - 1][1]);
    //ft_close_all(pipex);
    return(1);
}

void    ft_execute(tt_list *pipex, char **argv, char **envp)
{
    char **comando;
    int i;

    i = 0;
	if(pipex->heredoc == 0)
        comando = ft_splitpip(argv[pipex->comand + 3], ' ');
    else
        comando = ft_splitpip(argv[pipex->comand + 2], ' ');
    
    while(pipex->paths[i])
    {
    	pipex->paths[i]= ft_strjoinpip(pipex->paths[i], comando[0]);
    	if(access(pipex->paths[i], X_OK) != -1)
    		break;
    	i ++;
    }
    execve(pipex->paths[i], comando, envp);
}

void ifpid(tt_list *pipex, int argc, char **argv, char **envp)
{

   // dprintf(STDERR_FILENO, "ahola %d\n", (pipex->fd[1][0]));
    int file[2];
    if(pipex->comand == 0)
        first_child(pipex, &file[0], argv);
    if(pipex->pid == 0 && (pipex->comand != argc - 4 && (pipex->heredoc != 0) && pipex->comand != 0))
        middle_child(pipex);
    if (pipex->pid == 0 && (pipex->comand == argc - 4 || (pipex->heredoc == 0 && pipex->comand == argc - 5)))
        final_child(pipex, &file[1], argv, argc);
    if (pipex->pid == 0)
        ft_execute(pipex, argv, envp);
}

void    creationchilds(tt_list *pipex, int argc, char **argv, char **envp)
{
   int x;
   int i;
   
   i = 0;
   x = pipex->ncomand;
   if((pipex->fd = malloc(x * sizeof(int *))) == NULL)  
        return(0);
   while(x--)
   {
        if((pipex->fd[i] = malloc(2 * (sizeof(int)))) == NULL)
            return(0);
        pipe(pipex->fd[i++]);
   }
    i = 0;

    while(pipex->comand < pipex->ncomand)
    {
        pipex->pid = fork();
        if(pipex->pid == 0)
            break;
        if(pipex->pid < 0)
            exit(0);
        (pipex->comand)++;
    }
    ifpid(pipex, argc, argv, envp);
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
    pipex.paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
    *(pipex.paths) += 5;
    if (pipex.heredoc == 0)
        pipex.ncomand = argc - 4;
    if (argc < 5 || (pipex.heredoc == 0 && argc < 6))
		return(0);
    dprintf(STDERR_FILENO, "ola \n");
    creationchilds(&pipex, argc, argv, envp);
    dprintf(STDERR_FILENO, "jnjnjjn%d\n", pipex.comand);
    while(pipex.ncomand --)
        wait(NULL);
    return(0);
}