#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
    pid_t pid = fork();
    if(pid==0){
        //Child process
        sleep(1);
        printf("Child process, pid = %d\n", getpid());
        printf("My Parent's pid is = %d\n",getppid());
    }
    else if(pid>0){
        //Parent process
        printf("Parent Process, pid = %d\n",getpid());
        wait(NULL);
        printf("My Child's pid is = %d\n",pid);
    }
}