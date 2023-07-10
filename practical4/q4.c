#include <stdio.h>
#include <unistd.h>
int main()
{
    int id;
    printf("---Before Fork---\n");
    id = fork();
    if (id == 0)
    {
        /*child process*/
        printf("Child has started: %d\n ", getpid());
        printf("Parent of this child : %d\n", getppid());
        printf("child prints 1 item : \n ");
        sleep(10);
        printf("child prints 2 item :\n");
    }
    else
    {
        /*Parent Process*/
        printf("Parent for has started :%d \n", getpid());
        printf("Parent of the parent proc :%d \n", getppid());
    }
    printf("---After Fork---\n");
    return 0;
}