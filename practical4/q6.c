#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{ 
    printf("Files in Directory are:\n");
    execl("/bin/ls","ls", "-l",0);
    return 0;
}