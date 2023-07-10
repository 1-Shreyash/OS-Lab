#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define SIZE 10

struct MSG
{
    long int type;
    int a[SIZE];
}a1;
int main()
{
    int msgid;
    msgid = msgget(12, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error : %d ", errno);
        exit(EXIT_FAILURE);
    }
    if (msgrcv(msgid, &a1, sizeof(a1), 0, 0) == -1)
        {
            perror("msgcrv failed with error");
            exit(EXIT_FAILURE);
        }
    
    for(int i = 0 ; i < SIZE; i++)
        a1.a[i] *= a1.a[i];

    printf("Squares of all nums: ");
    for(int i = 0 ;i <SIZE; i++)
        printf("%d ",a1.a[i]);
    
    
}