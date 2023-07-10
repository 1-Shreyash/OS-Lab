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
    key_t key = 123;
    if ((msqid = msgget(key, 0644)) == -1)
    {
        printf("Server not active\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0)
    { // child
        // while (1)
        // {
            while (msgrcv(msqid, &mq, sizeof(mq.text), 1, 0) != -1)
            {
                if (mq.type == 1)
                {
                    printf("From Client: \"%s\"\n", mq.text);
                }
            }
        // }
    }
    else
    {//parent
        // wait(NULL);
        printf("Enter string:");
        while (fgets(mq.text, sizeof(mq.text), stdin) != NULL)
        {
            len = strlen(mq.text);
            if (mq.text[len - 1] == '\n')
                mq.text[len - 1] = '\0';
            mq.type = 0;
            msgsnd(msqid, &mq, len + 1, 0);
            printf("Enter string : ");
        }
        printf("Server Disconnected\n");
    }

    return 0;
}