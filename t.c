#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <errno.h>

///formatear salidas

///PRIMERO
int first_child(tt_list *pipex, int *file, char **argv)
{
    if(pipex->heredoc == 0)
    {
        int hd[2];

        pipe(hd);
        ft_heredoc(&hd[1], argv[2]);
        if (dup2(hd[0], STDIN_FILENO) < 0)
        	return(0);
        close(hd[1]);	
        close(hd[0]);
    }
    else
		{
			file[0] = open(argv[1], O_RDONLY);
			if(file[0] < 0)
				return(0);
			if (dup2(file[0], STDIN_FILENO) < 0)
				return(0);
		}
    if (dup2(pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
			return(0);

}

///MEDIO
int middle_child(tt_list *pipex)
{
    if(pipex->pid == 0 && (i != argc - 4 && (pipex->heredoc != 0) && i != 0))
    {
        if (dup2(pipex->fd[pipex->comand-1][0], STDIN_FILENO) < 0)
            return(0);
        if (dup2( pipex->fd[pipex->comand][1], STDOUT_FILENO) < 0)
            return(0);
        close(pipex->fd[pipex->comand][0]);
        close(pipex->fd[pipex->comand][1]);
    }
    return(0);
}


///ULTIMO

///crear hijos
void ft_place_comand(tt_list *pipex, int argc, char **argv, char **envp)
{
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
        ncomand --;
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
    pipex.ncomand = argc - 3;
    if (pipex.heredoc == 0)
        pipex.ncomand = argc - 4;
    pipex.paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
    *pipex.paths = *pipex.paths + 5;
    printf("PATH == %s\n", pipex.paths[0]);
    ft_create_childs_fd(&pipex);
    ft_place_comand(&pipex, argc, argv, envp);
    printf("hola soy el hijo == %d\n", pipex.comand);
    return (0);
}