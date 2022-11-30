#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    int ncomand;
    pid_t pid; 
    int	fd[2];
	pipe(fd);
	char **paths;
    int file;
	char *path;
	int p;

	pid = 1;
    ncomand = argc - 3;
	paths = (ft_split(ft_find_pathsenvp,  "PATH"), ":/");
	*paths += +5;

	/// see if access 
	///mirar las rutas de acceso que puedan execute

	while (*paths)
    {
        if(!access(*paths, X_OK))
		{
			paths - p;
			*paths = malloc(ft_strlen(path) * sizeof(char));
			*paths = paths + p;
			p = 0;
		}
		else
		{
			free(paths);
			p ++;
		}
        paths++;
    }
	
	///create childs
	//printf("pid ========= %d\n", pid);

    while(ncomand)
    {
        pid = fork();
		pipe(fd);
        if(pid > 0)
            break;
        if(pid < 0)
            return(0);
        ncomand --;
    }
	//        ###stdin == 0    ·····     ###stdout == 1      

	///formatear salidas     
    if (ncomand == argc - 3)
	{
		file = open(argv[0], O_RDONLY);
		if (!dup2(file, 0))
			return(0);
		if (!dup2(fd[1], 1))
			return(0);
		close(fd[0]);
	}

	else if (ncomand == 1)
	{
		file = open(argv[argc - 1], O_WRONLY);
		if (!dup2(file, 1))
			return(0);
		if (!dup2(fd[0], 0))
			return(0);
        close(fd[1]);
	}

	if(pid != 0 && ncomand != argc - 3 && ncomand != 1)
	{
		if (!dup2(fd[0], 0))
			return(0);
		if (!dup2(fd[1], 1))
			return(0);
	}
	/// hacer el execve
	if (pid == 0)
	{
		execve(path[ncomand], )
	}
	return(0);
}

///SI LO HE ENTENDIDO BIEN TENGO QUE PONER EN  
//EL SEGUNDO ARGUMENTO DE EXECVE EL ARGUMENTO DEL COMANDO 
//(POR EJEMPLO) (-la)
//tengo que crear una funcion que me coja los elementos
// (puedo usar ncomand para que me ayude a no repetir comandos )
//MUCHO CUIDADOOO QUE NCOMAND CUENTA DE ABAJO ARRIBA
