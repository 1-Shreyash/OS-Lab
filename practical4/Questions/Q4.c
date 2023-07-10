#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
    pid_t pid1 = fork();
    if(pid1 == 0){
        //child process
        printf("Inside child 1\n");
        exit(0);
    }
    
    pid_t pid2 = fork();
    if(pid2 == 0){
        //child process
        printf("Inside child 2\n");
        exit(0);
    }

    //This is parent process
    int w1, w2;
    waitpid(pid1, &w1, 0);
    waitpid(pid2, &w2, 0);
    printf("Now, in Parent process after executing both the childs\n");
}