// A C program to demonstrate Zombie Process.
// Child becomes Zombie as parent is sleeping
// when child process exits.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    // Fork returns process id

    // in parent process
    printf("--------Before fork--------\n");
    pid_t child_pid = fork();

    // Parent process
    if (child_pid > 0){
        printf("\nParent Process => Process id: %d\n",getpid());
        sleep(10);
    }

    // Child process
    else{
        printf("\nChild Process=> Process id: %d & it's Parent process id is: %d\n",getpid(),getppid());
        printf("Exiting Child Process !!!\n");
        exit(0);
    }
    
    printf("\n--------After fork--------\n");
    return 0;
}