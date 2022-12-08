#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    int ncomand;
    pid_t pid; 
	int	fd[2][2];
	char **paths;
    int file[2];
	char *path;
	int i;
	int p;

	i = 0;
	pid = 1;
    ncomand = 1;

	/////CREAR EL PATH
	paths = (ft_split(ft_find_paths(envp,  "PATH"), ':'));
	*paths += +5;
	p = 0;
	i = 0;
	//..............................

	/////CREAR LOS HIJOS Y LOS PIPES
    while(ncomand <= argc - 3)
    {
		//printf("%d\n", fd[i][0]);
		pipe(fd[i]);
        pid = fork();
        if(pid == 0)
            break;
        if(pid < 0)
            return(0);
        ncomand ++;
		i ++;
    }
	//.........................
	
	///        ###stdin == 0    ·····     ###stdout == 1      
	///FORMATEAR SALIDAS     
    if (ncomand == 1)
	{
		// int errnum = 0;
		// printf("%d\n", fd[i][0]);
		// if (dup2(STDOUT_FILENO, fd[i][1]) < 0)
		// 	printf("error %s\n", strerror(errnum));
		file[0] = open(argv[0], O_RDONLY);
		if (dup2(STDIN_FILENO, file[0]) < 0)
			return(0);
		if (dup2(STDOUT_FILENO, fd[i][1]) < 0)
			return(0);
		close(fd[i][0]);
		printf("hola soy %d% d\n", pid, fd[i][1]);
	}

	else if (ncomand == argc - 3)
	{
		file[1] = open(argv[argc - 1], O_WRONLY);
		if (dup2(STDOUT_FILENO, file[1]) < 0)
			return(0);
		if (dup2(STDIN_FILENO, fd[i][0]) < 0)
			return(0);
        close(fd[i][1]);
	}

	if(pid != 0 && ncomand != argc - 3 && ncomand != 1)
	{
		if (dup2(STDIN_FILENO, fd[i][0]) < 0)
			return(0);
		if (dup2(STDOUT_FILENO, fd[i][1]) < 0)
			return(0);
	}
		// printf("jojijijijii == %d\n", file[1]);

	i = 0;
	//.......................................
	// while(paths[x])
	// {
	// 	printf("%s\n", paths[x]);
	// 	x ++;
	// }
	if(pid == 0)
	{
		////PASAR LOS COMANDOS A ARRAY BIDIMENSIONAAL
		char **comando;
		comando = ft_split(argv[ncomand + 1], ' ');
		//................................

		/////METER EN LOS PATHS EL LA PRIMERA PALABRA DEL COMANDO
		while(paths[i])
		{
			//printf("antes == %s\n", paths[i]);
			paths[i] = ft_strjoin(paths[i], comando[0]);
			printf("despues == %s\n", paths[i]);
			printf("%d\n", access(paths[i], X_OK));
			// if(access(paths[i], X_OK) != -1)
			// {
			// 	printf("its ok =)");
			// 	break;
			// }
			i ++;
		}
		comando ++;
		// printf("hola soy == %d mi path es == %s\n", i, paths[i]);
		execve(paths[i], comando, envp);
		// printf("señorita poch\n");
	}
	wait(NULL);
	return(0);
}

///execve (path ,  argumentos del comando acabados en null, env)


///SI LO HE ENTENDIDO BIEN TENGO QUE PONER EN  
//EL SEGUNDO ARGUMENTO DE EXECVE EL ARGUMENTO DEL COMANDO 
//(POR EJEMPLO) (-la)
//tengo que crear una funcion que me coja los elementos
// (puedo usar ncomand para que me ayude a no repetir comandos )
//MUCHO CUIDADOOO QUE NCOMAND CUENTA DE ABAJO ARRIBA
