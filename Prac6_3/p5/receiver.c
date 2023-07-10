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
    char arr[SIZE];
}a1;

int main()
{
    int msgid;
    struct my_msg_st some_data;
    long int msg_to_recieve = 0;

    /* Let us set up the message queue */
    msgid = msgget(1234, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        perror("msgget failed with error");
        exit(EXIT_FAILURE);
    }

    /* Then the messages are retrieved from the queue, until an end message is
     * encountered. lastly the message queue is deleted
     */

    while (running)
    {
        if (msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_recieve, 0) == -1)
        {
            perror("msgcrv failed with error");
            exit(EXIT_FAILURE);
        }
        printf("You wrote: %s", some_data.some_text);
        if (strncmp(some_data.some_text, "end", 3) == 0)
        {
            running = 0;
        }
    }

    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        perror("msgctl(IPC_RMID) failed");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
    return 0 ;
}