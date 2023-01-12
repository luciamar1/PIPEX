#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <errno.h>


/*
void	ft_heredoc(int *file, char *delimitador)
{
	char *gnl;
	
	while(1)
	{
		gnl = get_next_line(STDIN_FILENO);
		if (ft_strncmp(gnl, delimitador, ft_strlen(delimitador)) == 0)
		{
			break;
		}
		while (*gnl)
			write(*file, gnl++, 1);
	}	
}

int main(int argc, char **argv, char **envp)
{
    int ncomand;
    pid_t pid; 
	int	fd[argc - 3][2];
	char **paths;
    int file[2];
	int i;
	int heredoc;

	//heredoc si == 0
	heredoc = ft_strncmp("here_doc", argv[1], 9);
	if( argc < 5 || (heredoc == 0 && argc < 6))
	{
		write(1, "faltan argumentos", 18);
		return(0);
	}

	i = 0;
    ncomand = 1;
	if(heredoc == 0)
		ncomand = 2;

	/////CREAR EL PATH
	paths = (ft_splitpip(ft_find_paths(envp,  "PATH"), ':'));
	//leaks

	//..............................

	/////CREAR LOS HIJOS Y LOS PIPES
	int x = argc -3;
	while(x--)
	{
		pipe(fd[i++]);
	}
	i = 0;

    while(ncomand <= argc - 3)
    {

        pid = fork();
        if(pid == 0)
		{
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

// //PRIMERO  

    if (i == 0)
	{
		if(heredoc == 0)
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
		if (dup2(fd[i][1], STDOUT_FILENO) < 0)
			return(0);

		// while(i)
		// {
		// 	close(fd[i][0]);
		// 	close(fd[i][1]);
		// 	i;
		// }
	}
// //MEDIO
if(pid == 0 && (i != argc - 4 && (heredoc != 0) && i != 0))
{
	if (dup2(fd[i-1][0], STDIN_FILENO) < 0)
		return(0);
	if (dup2( fd[i][1], STDOUT_FILENO) < 0)
		return(0);
	close(fd[i][0]);
	close(fd[i][1]);
}

// //ULTIMO
if (pid == 0 && (i == argc - 4 || (heredoc == 0 && i == argc - 5)))
{
	file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(file[1] < 0)
	{
		perror("error");
		return(0);
	}
	if (dup2(file[1], STDOUT_FILENO) < 0)
		return(0);
	if (dup2(fd[i-1][0], STDIN_FILENO) < 0)
		return(0);
	close(fd[i][0]);
	close(fd[i][1]);
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
while(i < 0)
{
	wait(NULL);
	ncomand --;
}
return(0);
}*/

// ///execve (path ,  argumentos del comando acabados en null, env)


// ///SI LO HE ENTENDIDO BIEN TENGO QUE PONER EN  
// //EL SEGUNDO ARGUMENTO DE EXECVE EL ARGUMENTO DEL COMANDO 
// //(POR EJEMPLO) (-la)
// //tengo que crear una funcion que me coja los elementos
// // (puedo usar ncomand para que me ayude a no repetir comandos )
// //MUCHO CUIDADOOO QUE NCOMAND CUENTA DE ABAJO ARRIBA
