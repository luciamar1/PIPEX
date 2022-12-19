# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>


// int main(int argc,char **argv,char **env)
// {
//     char *arguments[] = {"ls", "-l", NULL};
//     // printf("%d\n", access("/usr/bin/", X_OK));
//     execve("/bin/ls", arguments, env);
//     printf("error");
//     return(0);
// }
int main(void)
{
//    FILE *file;
// 	file = fopen ( "fichero.txt", "w+" );        
// 	if (file==NULL) {fputs ("File error",stderr); exit (1);}
// 	char *gnl;

// 	while(1)
// 	{
// 		gnl = get_next_line(fd);
// 		if (gnl == NULL | ft_strncmp(gnl, delimitador, ft_strlen(gnl)))
// 			break;
// 		while(gnl)
// 			write(file, gnl++, 1);
// 	}
// 	return(file);
	int ncomand;

	ncomand = 2;
	int argc = 3;
	while(ncomand <= argc)
	{
		ncomand++;
		printf("puta\n");
	}
}