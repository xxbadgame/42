#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
    int fd[2];
    if (pipe(fd) == -1){
        printf("An Error occured with opening the pipe\n");
    }
    int id = fork();
    if (id == 0) {
        close(fd[0]);
        int x;
        printf("input number: ");
        scanf("%d", &x);
        if(write(fd[1], &x, sizeof(int)) == -1)
            return 2;
        close(fd[1]);
    } else {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
            return 3;
        close(fd[0]);
        printf("Got from child process : %d\n", y);
    }

    return 0;
}