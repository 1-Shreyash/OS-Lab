#include <stdio.h>
#include <unistd.h>
int main(){
    int id;
    printf("---Before Fork---\n");
    id=fork();
    // if(id>0)
    // {
    // /*parent process*/
    // printf("This is parent section [Process id: %d].\n",getpid());
    // }
    if(id==0)
    {
    /*child process*/
        printf("child prints 1 item : \n ");
        sleep(10);
        printf("child prints 2 item :\n");
    }
    else 
    {
    /*fork creation failed*/
        printf("Parent for has started :%d \n",getpid());
        printf("Parent of the parent proc :%d \n",getppid());
    }
    printf("---After Fork---\n");
    return 0;
}