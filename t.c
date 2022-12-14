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
int [2]guatafac(void)
{
	int fd[2];
	pipe(fd);
	return(fd);
}

int main(void)
{
	int file[2];
	file = guatafac();
	printf(file[0]);
	printf(file[1]);
}