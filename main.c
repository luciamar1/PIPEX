#include "pipex.h"
#include <fcntl.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
    int ncomand;
    pid_t pid; 
	int	fd[argc - 3][2];
	char **paths;
    int file[2];
	int i;
	int p;
	if( argc < 5)
	{
		write(1, "faltan argumentos", 18);
		return(0);
	}
	pid = 1;
	i = 0;
    ncomand = 1;

	/////CREAR EL PATH
	paths = (ft_split(ft_find_paths(envp,  "PATH"), ':'));
	i = 0;
	*paths += +5;
	p = 0;
	//..............................

	/////CREAR LOS HIJOS Y LOS PIPES
    while(ncomand <= argc - 3)
    {
        pid = fork();
		pipe(fd[i]);
        if(pid == 0)
		{
			printf("%d\n", ncomand);
            break;
		}
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
		file[0] = open(argv[0], O_RDONLY);
		if (dup2(file[0], STDIN_FILENO) < 0)
			return(0);
		if (dup2(fd[i][1], STDOUT_FILENO) < 0)
			return(0);
		dprintf(STDOUT_FILENO, "hfiuehwoffheo    dffijeiorj3oi   %d\n", fd[i][1]);
		close(fd[i][0]);
	}

	else if (ncomand == argc - 3)
	{
		file[1] = open(argv[argc - 1], O_WRONLY);
		if (dup2(file[1], STDOUT_FILENO) < 0)
			return(0);
		if (dup2(fd[i-1][0], STDIN_FILENO) < 0)
			return(0);
		char *s;

		s = malloc(5 * 1);
		printf("hola guapa %zd\n", read(STDIN_FILENO, s, 5));

		write(2, s, 5);
	    close(fd[i][1]);
		close(fd[i][0]);
	}

	if(pid != 0 && ncomand != argc - 3 && ncomand != 1)
	{
		if (dup2(fd[i-1][0], STDIN_FILENO) < 0)
			return(0);
		if (dup2( fd[i][1], STDOUT_FILENO) < 0)
			return(0);
	}

	i = 0;
	if(pid == 0)
	{
		////PASAR LOS COMANDOS A ARRAY BIDIMENSIONAAL
		char **comando;
		comando = ft_split(argv[ncomand + 1], ' ');
		//................................

		/////METER EN LOS PATHS EL LA PRIMERA PALABRA DEL COMANDO
		while(paths[i])
		{
			paths[i] = ft_strjoin(paths[i], comando[0]);
			if(access(paths[i], X_OK) != -1)
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
