/*
 * Program to create orphan process @ Linux
 * getpid() gives process PID and 
 * getppid() gives process's parent ID 
 * here main() process ID is parent id is current shells PID
 * once process becomes orphan it is adopted by init process(it's PID is 1)
 */
#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t p;
    /* create child process */
    p = fork();
    if (p == 0)
    {
        /* fork() returns Zero to child */
        sleep(10);
    }
    printf("The child process pid is %d parent pid %d\n", getpid(), getppid());

    /*parent/child waits for 20 secs and exits*/
    sleep(20);
    printf("\nProcess %d is done its Parent pid %d...\n", getpid(), getppid());
    return 0;
}