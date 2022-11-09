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
	}

	if (ncomand == 0)
	{
		f = open(argv + 1);
		if (!dup2(f, stdout))
			return(NULL)
	}

	return(NULL);
}
