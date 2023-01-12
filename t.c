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
    pipex->fd = malloc(ncomand * sizeof(int *));
    if (pipex->fd == NULL)
            return(0);
    while(ncomand)
    {
        pipex->fd[counter] = malloc(2 * sizeof(int));
        if (pipex->fd[counter]== NULL)
            return(0);
        pipe(pipex->fd[counter]);
        printf("comando == %d\n", ncomand);
        counter ++;
    }
    while (pipex->comand < pipex->ncomand)
    {
        pipex->pid = fork();
        if (pipex->pid == 0)
            break;
        if (pipex->pid < 0)
            return(0);
        pipex->comand ++;
    }
    return(1);
}

int main(int argc, char **argv, char **envp)
{
    tt_list pipex;

    //heredoc si == 0
    pipex.heredoc = ft_strncmp("here_doc", argv[1], 9);
    pipex.heredoc = argc - 3; 
    pipex.comand = 0;
    if (pipex.heredoc == 0)
        pipex.ncomand = argc - 4;
    pipex.paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
    *pipex.paths = *pipex.paths + 5;
    printf("PATH == %s\n", pipex.paths[0]);
    ft_create_childs_fd(&pipex);
    printf("hola soy el hijo == %d\n", pipex.comand);
}