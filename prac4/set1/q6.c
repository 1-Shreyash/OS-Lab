#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
void main()
{ 
    printf("Files in Directory are:\n");
    execl("/bin/ls","ls", "-l",0);
}