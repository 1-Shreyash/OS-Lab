#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

void *Writer();
void *Reader();
int readCount = 0;
sem_t mutex, wrt;

char s[] = "notWritten";
int main()
{
    pthread_t wtid[5], rtid[10];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
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
    sem_wait(&wrt);

    int *value;
    sem_getvalue(&wrt, &value);
    printf("\n%d Writing, --Readcount = %d, --wrt = %d\n", myid, readCount, value);
    sprintf(s, "%d", myid);
    sleep(1);
    printf("%d Writer Completed writing!!!\n\n", myid);

    sem_post(&wrt);
}
void *Reader(void *vargp)
{
    int myid = (int)vargp;
    sleep(myid % 3);

    sem_wait(&mutex);
    readCount++;
    if (readCount == 1)
    {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    // read here
    int *value;
    sem_getvalue(&wrt, &value);
    printf("Reader %d , The string s is :%s, --Readcount =%d , --wrt = %d \n", myid, s, readCount, value);

    sem_wait(&mutex);

    readCount--;
    if (readCount == 0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);
}