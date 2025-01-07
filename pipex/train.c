#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    char *args[] = {"ls", "-ldrgers", NULL}; 
    if (execve("/bin/ls", args, envp) == -1)
    {
        perror("Exec error");
        exit(1);
    }

    return 0;
}