#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int status;
    pid_t fork_return;
    fork_return = fork();
    if(fork_return ==0){//child process
        sleep(2);
        printf("I'm in the child!!!\n");
        // sleep(2);
        exit(98);
    }
    else{//parent process
        printf("Parent!!\n");
        wait(&status);
        printf("I'm the parent!!!\n");
        if(WIFEXITED(status))
            printf("Child returned : %d \n",status>>8);
    }
    return 0;
}