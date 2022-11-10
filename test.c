# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pipe(fd);
	int f;
	pid_t	pid;
	int		ncomand;
	int		nchilds;
        char            **path;

	ncomand = argc - 4;
	argv + 3;	
	nchilds = 0;
	while (*argv )
	{
		if (**argv &&  ncomand != argc-4 && **argv == '"' && nchilds == 0)
		{
			pid = fork();
			ncomand --;
			nchilds ++;
			if (pid == 0)
				nchilds = 0;
			if (pid < 0)
				return (NULL);
		}	 
		argv --;
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

//CREO QUE DA IGUAL EL ORDEN DE EJECUCION DE PROCESOS
//HE COMUNICADO LOS PROCESOS ENTRE SI Y COMO TANTO EL DE LECTURA COMO EL DE ESCRITURA ESTAN ABIERTOS SE VAN A IR ESPERANDO 
//POR QUE HASTA Q EL DE ESCRITURA NO SE CIERRE EL DE LECTURA NO PUEDE LEER
//LO QUE NO SE ES SI VAN  A SEGUIR EL ORDEN POR QUE MI IDEA ES Q TODOS COMPARTAN EL MISMO PIPEX =) =O


///ME QUEDA AVERIGUAR COMO HACER EXECUTE PARA IR PROVANDO Y COMO ORGANIZAR LOS PROCESOS 
///PARA QUE CADA UNO HAGA SU COMANDO (ncomand) CREO QUE LO PODRE HACER TAMBIEN PUEDO 
///HACER FUNCION POR COMANDO NO SE JUJUUJUUUJUJ
