#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
// #include <time.h>
#define SIZE 100
typedef struct Memory
{
    // int a[SIZE];
    int min, max;
} Mem;

sem_t i;
// pthread_mutex_t mutex;
void initialize()
{
    sem_init(&i, 1, 1);
}
int main()
{
    // clock_t start, end;
    // start = clock();
    int shmid;
    key_t key;
    Mem *shm;
    initialize();
    int a[SIZE];
    if ((shmid = shmget(IPC_PRIVATE, sizeof(Mem), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (Mem *)-1)
    {
        perror("shmat");
        exit(1);
    }
    printf("The array elements are:\n");
    // initialising 100 variables
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 1000;
        printf("%d ", a[i]);
    }
    pid_t pid = fork();
    if (pid == 0)
    {
        // child process
        shm->max = a[0], shm->min = a[0];
        for (int i = 0; i < SIZE / 2; i++)

        {
            sem_wait(&i);
            if (a[i] > shm->max)
                shm->max = a[i];
            if (a[i] < shm->min)
                shm->min = a[i];
            sem_post(&i);
        }
    }
    else if (pid > 0)
    {
        
        for (int i = SIZE / 2; i < SIZE; i++)
        {
            sem_wait(&i);
            if (a[i] > shm->max)
                shm->max = a[i];
            if (a[i] < shm->min)
                shm->min = a[i];
            sem_post(&i);
        }
        wait(NULL);
        printf("\nThe max value is: %d\n", shm->max);
        printf("The min value is: %d\n", shm->min);
        shmdt((void *)shm);
        // shmctl(shmid, IPC_RMID, NULL);
        // end = clock();
        // printf("Time diff = %lu", end - start);
    }
    return 0;
}