#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *Writer();
void *Reader();
int readCount = 0;
int writeCount = 1;
pthread_cond_t WriterIn = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar = PTHREAD_MUTEX_INITIALIZER;

char s[] = "notWritten";
int main()
{
    pthread_t wtid[5], rtid[10];
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&wtid[i], NULL, Writer, i);
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&rtid[i], NULL, Reader, i);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(wtid[i], NULL);
    for (int i = 0; i < 10; i++)
        pthread_join(rtid[i], NULL);
    printf("Completed ;)");
    return 0;
}
void *Writer(void *vargp)
{
    int myid = (int)vargp;
    sleep(myid);

    pthread_mutex_lock(&mVar);

        if(writeCount == 0)
            pthread_cond_wait(&WriterIn, &mVar);
        writeCount--;

        printf("\n%d Writing, --Readcount = %d, --WriteCount = %d\n", myid ,readCount ,writeCount);
        sprintf(s,"%d",myid);
        sleep(1);
        printf("%d Writer Completed writing!!!\n\n",myid);

        writeCount++;
        pthread_cond_broadcast(&WriterIn);

    pthread_mutex_unlock(&mVar);
}
void *Reader(void *vargp)
{
    int myid = (int)vargp;
    sleep(myid%3);
    pthread_mutex_lock(&mVar);
        readCount++;
        if(readCount == 1){
            if(writeCount == 0)
                pthread_cond_wait(&WriterIn, &mVar);
            writeCount--;
        }
    pthread_mutex_unlock(&mVar);

        //read here
        printf("Reader %d , The string s is :%s, --Readcount =%d , --WriteCount = %d \n",myid ,s ,readCount ,writeCount);

    pthread_mutex_lock(&mVar);
        readCount--;
        if(readCount == 0){
            writeCount++;
            pthread_cond_broadcast(&WriterIn);
        }
    pthread_mutex_unlock(&mVar);
}