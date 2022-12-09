# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>


int main(int argc,char **argv,char **env)
{
    char *arguments[] = {"ls", "-l", NULL};
    // printf("%d\n", access("/usr/bin/", X_OK));
    execve("/bin/ls", arguments, env);
    printf("error");
    return(0);
}