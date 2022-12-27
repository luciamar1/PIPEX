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

void    creationchilds(int **fd, int *ncomand, int *comand, int *pid)
{
   int x;
   int i;

   i = 0;
   x = *ncomand;
   while(x--)
   {
        pipe(fd[i++]);
        printf("puta\n");
   }
    x = 2;
    i = 0;
    while(x--)
        dprintf(STDERR_FILENO, "caracola en vinagre %d\n", (fd[i++][0]));
    while(*comand < *ncomand)
    {
        *pid = fork();
        if(*pid == 0)
        {
            dprintf(STDERR_FILENO, "%d\n", *comand);
            break;
        }
        if(*pid < 0)
            exit(0);
        (*comand)++;
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

ifpid(int ncomand, int heredoc)

int main(int argc, char **argv, char **envp)
{
    tt_list pipex;
    int	**fd;
    // int heredoc;
    // int ncomand;
    // int comand;
    // int pid;

    // *envp = NULL;
    //heredoc si == 0
    pipex.comand = 0;
    pipex.heredoc = ft_strncmp("here_doc", argv[1], 9);
    pipex.ncomand = argc - 3;
    pipex.paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
    fd = ft_malloc(pipex.ncomand, fd);
    if (fd == NULL)
        return(0);
    *(pipex.paths) += 5;

    if (pipex.heredoc == 0)
        pipex.ncomand = argc - 4;
    if (argc < 5 || (pipex.heredoc == 0 && argc < 6))
		return(0);
    creationchilds(fd, &pipex.ncomand,  &pipex.comand, &pipex.pid);
    ifpid(pipex.comand, pipex.heredoc);
    return(0);
}