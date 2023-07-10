// In this program fork pid, ppid will be demonstrated
//  Initially child will have one parent,after the death of its father it will be assigned another father
//  named init process. This can be checked by noting down the new ppid and running ps- el. run the program in background by concanating & at the end.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
void main()
{
    int pid1, pid, ppid;\
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("I am child process \n");
        printf("child pid is %d\n", getpid());
        printf("child ppid is %d\n", getppid());
        printf("\n");
        sleep(10);
        printf("now child pid is %d\n", getpid());
        printf("now child ppid is %d\n", getppid());
    }
    if (pid1 > 0)
    {
        printf("I am parent process \n");
        printf("parent pid is %d\n", getpid());
        printf("parent's ppid is %d\n", getppid());
        printf("\n");
    }
}