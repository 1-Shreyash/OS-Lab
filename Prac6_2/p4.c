#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pipefd[2], n, pid;
    char buff[100];
    pipe(pipefd);
    printf("\n readfd=%d\n", pipefd[0]);
    printf("\n writefd=%d\n", pipefd[1]);
    write(pipefd[1], "hello", 5);
    pid = fork();
    if (pid == 0)
    {
        // sleep(2);
        // return 0;
        close(pipefd[0]);//closing read
        printf("\n CHILD PROCESS SENDING DATA\n");
        write(pipefd[1], "hi", 2);
        printf("Hibi\n");
    }
    else
    {   
        // wait(NULL); 
        close(pipefd[1]);//closing write
        printf("PARENT PROCESS RECEIVES DATA\n");
        n = read(pipefd[0], buff, 100);
        printf("\n size of data :%d", n);
        printf("\n data received from child through pipe:%s\n", buff);
    }
    return 0;
}