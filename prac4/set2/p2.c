#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
void main()
{
    int pid1, pid, ppid;
    pid1 = fork();
    if (pid1 > 0)
    {
        printf("I am parent process \n");
        printf("parent pid is %d\n", getpid());
        printf("parent's ppid is %d\n", getppid());
        // printf("\n");
        sleep(10);
        printf("hi");
    }
}