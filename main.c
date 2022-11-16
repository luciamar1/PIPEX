# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int ncomand;
    pid_t pid;
    int	fd[2];
	int	pipe(fd);
    int file;

    ncomand = argc - 3;
    while(ncomand)
    {
        pid = fork();
        if(pid == 0)
            break;
        if(pid < 0)
            return(0);
        ncomand --;
    }
    if (pid == 0)
        printf("HOLA SOY EL PROCESO == %d\n", getpid());
    if (pid > 0)
    {
        wait(NULL);
        printf("ADIOS SOY EL PROCESO == %d\n", getpid());
    }
    if (ncomand = argc - 3;)
	{
		file = open(argv[0]);
		if (!dup2(file, stdin))
			return(NULL)
		if (!dup2(fd[1], stdout))
			return(NULL)
		close(fd[0]);
	}

	if (ncomand == 1)
	{
		file = open(argv[argc - 1]);
		if (!dup2(file, stdout))
			return(NULL)
		if (!dup2(fd[0], stdin))
			return(NULL);
        close(fd[1]);
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
