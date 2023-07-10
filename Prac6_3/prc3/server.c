#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include<unistd.h>

struct mesgq
{
    long type;
    char text[200];
    // long counts = 0, countc = 0;
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

    pid_t pid = fork();
    if (pid == 0)
    {
        // child process to read data
        while (1)
        {
            while (msgrcv(msqid, &mq, sizeof(mq.text), 1, 0) != -1)
            {
                if (mq.type == 0)
                {
                    printf("From Client: \"%s\"\n", mq.text);
                }
            }
        }
    }
    else
    { // parent process to send data
        printf("Enter string:");
        while (fgets(mq.text, sizeof(mq.text), stdin) != NULL)
        {
            len = strlen(mq.text);
            if (mq.text[len - 1] == '\n')
                mq.text[len - 1] = '\0';
            mq.type = 1;
            msgsnd(msqid, &mq, len + 1, 0);
            printf("Enter string : ");
        }
    }
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}