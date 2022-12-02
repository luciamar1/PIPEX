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
    ncomand = 1;

	/////CREAR EL PATH
	paths = (ft_split(ft_find_paths(envp,  "PATH"), ':'));
	*paths += +5;
	p = 0;
	int i = 0;
	int x = 0;
	//..............................

	/////CREAR LOS HIJOS Y LOS PIPES
    while(ncomand <= argc - 3)
    {
		pipe(fd);
        pid = fork();
        if(pid == 0)
            break;
        if(pid < 0)
            return(0);
        ncomand ++;
    }
	printf("hola soy %d\n%d\n", pid, fd[1]);
	//.........................
	
	///        ###stdin == 0    ·····     ###stdout == 1      
	///FORMATEAR SALIDAS     
    if (ncomand == 1)
	{
		file = open(argv[0], O_RDONLY);
		if (dup2(file, 0) < 0)
			return(0);
		if (dup2(fd[1], 1) < 0)
			return(0);
		printf("hola\n");
		close(fd[0]);
	}

	else if (ncomand == argc - 3)
	{
		file = open(argv[argc - 1], O_WRONLY);
		if (dup2(file, 1) < 0)
			return(0);
		if (dup2(fd[0], 0) < 0)
			return(0);
        close(fd[1]);
	}

	if(pid != 0 && ncomand != argc - 3 && ncomand != 1)
	{
		if (dup2(fd[0], 0) < 0)
			return(0);
		if (dup2(fd[1], 1) < 0)
			return(0);
	}

	i = 0;
	//.......................................
	// while(paths[x])
	// {
	// 	printf("%s\n", paths[x]);
	// 	x ++;
	// }
	if(pid > 0)
	{
		////PASAR LOS COMANDOS A ARRAY BIDIMENSIONAAL
		char **comando;
		comando = ft_split(argv[ncomand], ' ');
		//................................

		/////METER EN LOS PATHS EL LA PRIMERA PALABRA DEL COMANDO
		while(paths[i])
		{
			ft_strjoin(paths[i], comando[0]);
			if(!access(paths[i], X_OK))
				break;
			i ++;
		}
		execve(paths[i], comando, envp);
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
