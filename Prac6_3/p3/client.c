/*Program: Write a C program in Linux to implement Chat application using message queue.
Code for Client
Client chat process - climsg.c */

#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    printf("Client ready :\n");


    while (1)
    {
        /* code */int opt = 0;
    printf("Enter 1 to type else 0: ");
    scanf("%d", &opt);
    if (opt == 1)
    {
        if (mq.type != 1)
        {
            printf("Enter text, ^D to quit:\n");

            mq.type = 1;
            while (fgets(mq.text, sizeof(mq.text), stdin) != NULL)
            {
                len = strlen(mq.text);
                if (mq.text[len - 1] == '\n')
                    mq.text[len - 1] = '\0';
                msgsnd(msqid, &mq, len + 1, 0);
                // mq.type = 0;
                // msgrcv(msqid, &mq, sizeof(mq.text), 1, 0);
                // while(mq.type == 2){
                //     printf("From Client: \"%s\"\n", mq.text);
                //     msgrcv(msqid, &mq, sizeof(mq.text), 1, 0);
                // }
            }
            // mq.type = 1;
        }
    }
    else
    {
        while (msgrcv(msqid, &mq, sizeof(mq.text), 1, 0) != -1)
        {
            if (mq.type == 1)
                printf("From server : \"%s\"\n", mq.text);
            // while(fgets(mq.text, sizeof(mq.text), stdin) != NULL)
            // {
            //     mq.type = 1;
            //     len = strlen(mq.text);
            //     if (mq.text[len - 1] == '\n')
            //         mq.text[len - 1] = '\0';
            //     msgsnd(msqid, &mq, len + 1, 0);
            // }
        }
    }
    }
    
    
    printf("Server Disconnected\n");
    return 0;
}