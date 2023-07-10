#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void *producer(); /* the thread */
void *consumer(); /* the thread */
int main()
{
    pthread_t ptid, ctid; // Thread ID
    pthread_create(&ptid, NULL, producer, NULL);
    pthread_create(&ctid, NULL, consumer, NULL);

    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);
    return 0;
}
// The thread will begin control in this function
void *producer(void *param)
{
    do
    {
        printf("I'm producer\n");
    } while (1);
    pthread_exit(0);
}
// The thread will begin control in this function
void *consumer(void *param)
{
    do
    {
        printf("I'm consumer\n");
    } while (1);
    pthread_exit(0);
}
