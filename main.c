#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    int ncomand;
    pid_t pid; 
    int	fd[2];
	pipe(fd);
	char **path;
    int file;
	pid = 1;
    ncomand = argc - 3;
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
	path = (ft_split(ft_find_path(envp,  "PATH"), ":/"));
	*path += +5;
	while (*path)
    {
        printf("%s\n", *path);
        path++;
    }
	return(0);
}

//CREO QUE DA IGUAL EL ORDEN DE EJECUCION DE PROCESOS
//HE COMUNICADO LOS PROCESOS ENTRE SI Y COMO TANTO EL DE LECTURA COMO EL DE ESCRITURA ESTAN ABIERTOS SE VAN A IR ESPERANDO 
//POR QUE HASTA Q EL DE ESCRITURA NO SE CIERRE EL DE LECTURA NO PUEDE LEER
//LO QUE NO SE ES SI VAN  A SEGUIR EL ORDEN POR QUE MI IDEA ES Q TODOS COMPARTAN EL MISMO PIPEX =) =O


///ME QUEDA AVERIGUAR COMO HACER EXECUTE PARA IR PROVANDO Y COMO ORGANIZAR LOS PROCESOS 
///PARA QUE CADA UNO HAGA SU COMANDO (ncomand) CREO QUE LO PODRE HACER TAMBIEN PUEDO 
///HACER FUNCION POR COMANDO NO SE JUJUUJUUUJUJ
