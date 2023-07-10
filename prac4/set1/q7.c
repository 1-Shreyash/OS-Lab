#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include<sys/types.h>
#define BUF_SIZE 100
void ChildProcess();
void ParentProcess();
void Child1Process();
void main()
{
    pid_t pid;
    pid = fork();
    if (pid == 0)
        ChildProcess();
    else
        ParentProcess();
}
void ChildProcess()
{
    int i;
    char *args[] ={"ls","-l",0};
    execvp("ls", args);
}
void ParentProcess()
{
    int i, t;
    char b[BUF_SIZE];
    char buffer[5];

    int f1, f2, ret;
    pid_t pid1;
    pid1 = fork();
    if (pid1 == 0)
        Child1Process();
    else
    {
        f1 = open("t1.txt",O_RDONLY|O_CREAT, 0777);
        if (f1 == -1)
            write(1, " Error while  opening file !!!!!", 36);
        f2 = open("t3.txt",O_WRONLY | O_CREAT, 0777);
        if (f2 == -1)
            write(1,"Error while opening file !!!!!!", 36);
        else
            do
            {
                ret = read(f1, buffer, sizeof(buffer));
                if (ret)
                {
                    ret = write(f2, buffer, sizeof(buffer));
                }
            } while (ret);
    }
    i = wait(NULL);
    if (i != -1)
        printf("PID = % d ", i);
    i = wait(NULL);
    if (i != -1)
        printf(" PID = % d ", i);
}
void Child1Process()
{
    int i;
    long int sum = 0;
    for (i = 1; i<=1000; i++)
        sum += i;
    printf(" CHILD CALCULATED TOTAL = % ld\n ", sum);
}