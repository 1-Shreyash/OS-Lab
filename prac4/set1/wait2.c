#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
void waitexample(){
    int i, stat;
    pid_t pid[5];
    for(i =0; i<5;i++){
        if((pid[i] = fork())==0){
            printf("hi");
            sleep(1);
            exit(100+i);
        }
    }
    //Usingf waitpid() and printing exit status of children
    for(i=0;i<5;i++){
        pid_t cpid = waitpid(pid[i], &stat, 0);
        if(WIFEXITED(stat))
            printf("Child %d terminated with status : %d \n ", cpid , WIFEXITED(stat));
    }
}
int main(){
    waitexample();
    return 0;
}