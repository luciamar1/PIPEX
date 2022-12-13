#include "pipex.h"
#include <fcntl.h>
#include <fcntl.h>

void	heredoc(int **fd, char *delimitador)
{
	char *gnl;
	pipe(*fd);
	while(1)
	{
		gnl = get_next_line(STDIN_FILENO);
		if (gnl == NULL || ft_strncmp(gnl, delimitador, ft_strlen(gnl)))
			break;
		while(gnl || ft_strncmp(gnl, delimitador, ft_strlen(gnl)))
			write(*fd[0], gnl++, 1);
}

int main(int argc, char **argv, char **envp)
{
    int ncomand;
    pid_t pid; 
	int	fd[argc - 4][2];
	char **paths;
    int file[2];
	int i;
	if( argc < 5 || (ft_strncmp("here_doc", argv[1], 9) == 0 && argc < 6))
	{
		write(1, "faltan argumentos", 18);
		return(0);
	}
	pid = 1;
	i = 0;
    ncomand = 1;

	/////CREAR EL PATH
	paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
	//leaks
	*paths += +5;
	//..............................

	/////CREAR LOS HIJOS Y LOS PIPES
    while(ncomand <= argc - 3)
    {
		pipe(fd[i]);
        pid = fork();
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
		if(ft_strncmp("here_doc", argv[1], 9) == 0)
			heredoc(&file, argv[2]);
		else
			file[0] = open(argv[0], O_RDONLY);
		if(file[0] < 0)
			return(0);
		if (dup2(file[0], STDIN_FILENO) < 0)
			return(0);
		if (dup2(fd[i][1], STDOUT_FILENO) < 0)
			return(0);
		// dprintf(STDOUT_FILENO, "hfiuehwoffheo    dffijeiorj3oi   %d\n", fd[i][1]);
		// dprintf(fd[i][1], "second line: %d\n", fd[i][1]);
		close(fd[i][0]);
	}

	else if (ncomand == argc - 3)
	{
		file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
		if(file[1] < 0)
			return(0);
		if (dup2(file[1], STDOUT_FILENO) < 0)
			return(0);
		if (dup2(fd[i-1][0], STDIN_FILENO) < 0)
		...................................



			return(0);
		char *s;

		s = malloc(5 * 1);
		// printf("hola guapa %zd\n", read(STDIN_FILENO, s, 5));

		//write(2, s, 5);
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
		comando = ft_splitpip(argv[ncomand + 1], ' ');
		//................................

		/////METER EN LOS PATHS EL LA PRIMERA PALABRA DEL COMANDO
		while(paths[i])
		{
			paths[i] = ft_strjoinpip(paths[i], comando[0]);
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
