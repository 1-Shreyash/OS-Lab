#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// int main(){
//     // int id;
//     printf("Hello, World!\n");
//     fork();
//     printf("Bye\n");
//     return 0;
// }
// #include &lt;stdio.h&gt;
// #include &lt;unistd.h&gt;
#include <stdio.h>
#include <unistd.h>
int main()
{
    int id;
    int x = 5;
    printf("Hello, World!\n");
    id = fork();
    id = fork();
    if (id > 0)
    {
        /*parent process*/
        printf("------------------------------\n");
        printf("This is parent section [Process id: %d].\n", getpid());
        printf("x value: %d\n",x);
        x+=5;
    }
    else if (id == 0)
    {
        /*child process*/
        printf("------------------------------\n");
        printf("fork created [Process id: %d].\n", getpid());
        // printf("hi hello\n");
        // sleep(1);
        printf("fork parent process id: %d.\n", getppid());
        // sleep(1);
        sleep(5);
    }
    else
    {
        /*fork creation failed*/
        printf("fork creation failed!!!\n"); // this must come same as parent process id as in parent in ubuntu
    }
    printf("Print the numbers from 0 to 9 :");
    for(int i=0;i<10;i++){
        printf("%d ",i);
    }
    printf("\n");
    sleep(10);
    return 0;
}