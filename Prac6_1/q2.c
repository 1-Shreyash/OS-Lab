#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
// #include <time.h>

#define SIZE 100

typedef struct Memory
{
    // int a[SIZE];
    int min, max;
} Mem;

int main()
{
    // clock_t start, end;
    // start = clock();
    int shmid;
    key_t key;
    Mem *shm;
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
            if (a[i] > shm->max)
                shm->max = a[i];
            if (a[i] < shm->min)
                shm->min = a[i];
        }
    }
    else if (pid > 0)
    {
        int max2 = a[SIZE / 2 + 1], min2 = a[SIZE / 2 + 1];
        for (int i = SIZE / 2; i < SIZE; i++)
        {
            if (a[i] > max2)
                max2 = a[i];
            if (a[i] < min2)
                min2 = a[i];
        }
        wait(NULL);
        shm->max = shm->max > max2 ? shm->max : max2;
        shm->min = shm->min > min2 ? min2 : shm->min;
        printf("\nThe max value is: %d\n", shm->max);
        printf("The min value is: %d\n", shm->min);
        shmdt((void *)shm);
        // shmctl(shmid, IPC_RMID, NULL);
        // end = clock();
        // printf("Time diff = %lu", end - start);
    }
    return 0;
}