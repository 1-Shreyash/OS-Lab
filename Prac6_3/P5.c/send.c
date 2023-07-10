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
void swap(int *a,int *b){
    int c;
    c=*b;
    *b=*a;
    *a=c;
}
int main()
{
    for(int i = 0 ;i< SIZE ; i++){
        a1.a[i] = rand() % 10 ;
        printf("%d ", a1.a[i]);
    }
    printf("\n");
    for(int i=0;i<SIZE-1;i++){
        int min_index=i;
        for(int j=i+1;j<SIZE;j++){
            if(a1.a[min_index]>=a1.a[j])
                min_index=j;
        }
        if(i!=min_index)
        swap(&a1.a[i],&a1.a[min_index]);
    }
    for(int i = 0 ;i< SIZE ; i ++){
        printf("%d ",a1.a[i] );
    }
    int msgid;
    msgid = msgget(12, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error : %d ", errno);
        exit(EXIT_FAILURE);
    }
    a1.type = 1;
    if (msgsnd(msgid,&a1, sizeof(a1), 0) == -1)
        {
            // perror("msgsnd error");
            fprintf(stderr, "msgsnd failed ");
            exit(EXIT_FAILURE);
        }
}