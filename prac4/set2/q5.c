#include <stdio.h>;
void main()
{
printf("After exec my pid is %d\n",getpid());
printf("After exec my ppid is %d\n",getppid());
printf("exec ends\n");
}