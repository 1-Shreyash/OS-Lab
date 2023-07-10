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
    long type;
    char text[200];
} mq;

int main()
{
    int msqid, len;
    key_t key = 345;
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1)
    {
        perror("msgget error");
        exit(1);
    }
    printf("Server ready :\n");
    printf("Enter text, ^D to quit:\n");
    mq.type = 1;
    while (fgets(mq.text, sizeof(mq.text), stdin) != NULL)
    {
        len = strlen(mq.text);
        if (mq.text[len - 1] == '\n')
            mq.text[len - 1] = '\0';
        msgsnd(msqid, &mq, len + 1, 0);
    }
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}