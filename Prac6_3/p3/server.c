/*Code for server
 Server chat process - srvmsg.c */

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct mesgq
{
    long type; // 1 for server, 2 for client
    char text[200];
} mq;

int main()
{
    int msqid, len;
    key_t key = 123;
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1)
    {
        perror("msgget error");
        exit(1);
    }
    printf("Server ready :\n");

    while (1)
    {
        int opt = 0;
        printf("Enter 1 to type else 0: ");
        scanf("%d", &opt);
        if (opt == 1)
        {
            // if (mq.type != 1)
            // {
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
                // mq.type = 0;
            // }
            // else
            //     printf("Can't type, Client is typing!!");
        }
        else
        {
            while (msgrcv(msqid, &mq, sizeof(mq.text), 1, 0) != -1)
            {
                if (mq.type == 1)
                    printf("From Client : \"%s\"\n", mq.text);
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

    msgctl(msqid, IPC_RMID, NULL);
    printf("hello");
    return 0;
}