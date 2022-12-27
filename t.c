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
// int [2]guatafac(void)
// {
// 	int fd[2];
// 	pipe(fd);
// 	return(fd);
// }

// int main(void)
// {
// 	int file[2];
// 	file = guatafac();
// 	printf(file[0]);
// 	printf(file[1]);
// }
#include <stdio.h>

int Valor(int);
int Referencia(int*);

int main(void)
{
    int array[30];
    array[4] = 33;
    
    printf("Posicion 5, Valor: %d\r\n", Valor(array[4]));
    printf("Posicion 5, Valor: %d\r\n", array[4]);
    printf("Posicion 5, Referencia %d\r\n", Referencia(&array[4]));
    printf("Posicion 5, Referencia %d\r\n", array[4]);
    
    return 0;
}

int Valor(int v)
{
  return v;
}


int Referencia(int *r)
{
  return (*r)++;
}