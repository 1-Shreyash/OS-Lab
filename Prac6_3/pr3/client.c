/*Program: Write a C program in Linux to implement Chat application using message queue.
Code for Client
Client chat process - climsg.c */

#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

struct mesgq
{
    long type;
    char text[200];
} mq;

int main()
{
    int msqid, len;
    key_t key = 345;
    if ((msqid = msgget(key, 0644)) == -1)
    {
        printf("Server not active\n");
        exit(1);
    }
    printf("Client ready :\n");
    // sleep(5);
    while (msgrcv(msqid, &mq, sizeof(mq.text), 1, 0) != -1)
    {
        printf("From Server: \"%s\"\n", mq.text);
    }
    printf("Server Disconnected\n");
    return 0;
}