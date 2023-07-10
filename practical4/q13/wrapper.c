#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    printf("This is wrapper file!!\n");
    execl("parmax","parmax", (char *)0);
}