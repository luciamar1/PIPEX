#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

extern int counter;

// int main(void) {
//     int fd = open("archivo2.txt", O_WRONLY | O_APPEND);

//     printf("archivo2.txt fd = %d\n", fd);
//     dup2(fd, 121);
   
//  dprintf(121, "This string will be printed in archivo2.txt file\n");
//     exit(EXIT_SUCCESS);
// }

int main(void)
{
	int pid;
	int fd[2][2];
	int x = 2;
	while(x--)
	{
		pid = fork();
		pipe(fd);
	}
	
}