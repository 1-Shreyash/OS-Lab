#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFSIZE 5
int shelf = 0;
sem_t full, empty, mutex;

void *cook(void *arg)
{
    int myid = (int)arg;
    sem_wait(&empty);
    sem_wait(&mutex);
    printf("\n\nThe number of current pizzas: %d\n", shelf);
    shelf++;
    printf("Cook %d: Cooked a pizza, there are %d pizzas now.\n", myid, shelf);
    sem_post(&mutex);
    sem_post(&full);
}
void *waiter(void *arg)
{
    int myid = (int)arg;
    sem_wait(&full);
    sem_wait(&mutex);
    printf("\n\nThe number of current pizzas: %d\n", shelf);
    shelf--;
    printf("Waiter %d : I picked up a pizza --, no. of pizzas now :%d \n", myid, shelf);
    sem_post(&mutex);
    sem_post(&empty);
}
int main()
{
    pthread_t Tcook[10], Twaiter[15];
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFSIZE);
    sem_init(&mutex, 0, 1);
    printf("Restuarent Opened!!!\n");
    for (int i = 0; i < 7; i++)
        pthread_create(&Tcook[i], NULL, cook, i);
    for (int i = 0; i < 10; i++)
        pthread_create(&Twaiter[i], NULL, waiter, i);
    for (int i = 0; i < 7; i++)
        pthread_join(Tcook[i], NULL);
    for (int i = 0; i < 10; i++)
        pthread_join(Twaiter[i], NULL);
    printf("Restuarent Closed!!!\n");
    return 0;
}