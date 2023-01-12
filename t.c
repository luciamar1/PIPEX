#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <errno.h>

int ft_create_childs_fd(tt_list *pipex)
{
    int ncomand;
    int counter;

    ncomand = pipex->ncomand;
    counter = 0;
    pipex->fd = malloc(x * sizeof(int *));
    while(x)
    {
        pipex->fd[counter] = malloc(2 * sizeof(int));
        pipe(pipex->fd[counter]);
        counter ++;
    }
    while (pipex->comand < pipex->comand)
    {
        pipex->pid = fork();
        if (pipex->pid == 0)
            break;
        if (pipex->pid < 0)
            return(0);
        pipex->comand ++;
    }
}

int main(int argc, char **argv, char **envp)
{
    tt_list pipex;

    //heredoc si == 0
    pipex.heredoc = ft_strncmp("here_doc", argv[1], 9);
    pipex.heredoc = argc - 3; 
    if (pipex.heredoc == 0)
        pipex.ncomand = argc - 4;
    pipex.paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
    ft_create_childs_fd(&pipex);
}