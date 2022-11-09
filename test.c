# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>

int main (int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pipe(fd);
	int f;
	pid_t	pid;
	int		ncomand;

	ncomand = argc - 4;
	argv + 3;	
	if (**argv && **argv == '"')
	{
		pid = fork();
		ncomand --;
		if (pid < 0)
			return (NULL);
	}	 

	if (ncomand == argc - 4)
	{
		f = open(argv - 1);
		if (!dup2(f, stdin))
			return(NULL)
		if (!dup2(fd[1], stdout))
			return(NULL)
		close(fd[0]);
	}

	if (ncomand == 0)
	{
		f = open(argv + 1);
		if (!dup2(f, stdout))
			return(NULL)
		if (!dup2(fd[0], stdin))
			return(NULL)
	}

	else
	{
		if (!dup2(fd[0], stdin))
			return(NULL)
		if (!dup2(fd[1], stdout))
			return(NULL)
	}
	return(NULL);
}

//HE COMUNICADO LOS PROCESOS ENTRE SI Y COMO TANTO EL DE LECTURA COMO EL DE ESCRITURA ESTAN ABIERTOS SE VAN A IR ESPERANDO 
//POR QUE HASTA Q EL DE ESCRITURA NO SE CIERRE EL DE LECTURA NO PUEDE LEER
//LO QUE NO SE ES SI VAN  A SEGUIR EL ORDEN POR QUE MI IDEA ES Q TODOS COMPARTAN EL MISMO PIPEX =) =O
