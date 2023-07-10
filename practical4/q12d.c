#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("before exec my pid is %d\n", getpid());
    printf("before exec my ppid is %d\n", getppid());
    printf("exec starts\n");
    execl("first_e", "first_e", (char *)0);
    printf("This will not print\n");
    return 0;
}