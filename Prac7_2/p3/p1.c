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
typedef struct Memory
{
    // int a[SIZE];
    int a;
    sem_t sem;
} Mem;

// pthread_mutex_t mutex;

int main()
{
    // clock_t start, end;
    // start = clock();
    int shmid;
    key_t key;
    Mem *shm;
    if ((shmid = shmget(1234, sizeof(Mem), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (Mem *)-1)
    {
        perror("shmat");
        exit(1);
    }
    sem_init(&shm->sem, 1, 1);
    shm->a = 0;
    pid_t pid = fork();
    if (pid == 0)
    {
        // child process
        sleep(2);
        for(int i = 0; i<5;i++){

            sem_wait(&shm->sem);
            printf("\nC The current value of a is : %d\n",shm->a);
            shm->a++;
            sleep(1);
            printf("C changed the value of a: %d\n",shm->a);
            sem_post(&shm->sem);
        }

    }
    else if (pid > 0)
    {
        for(int i = 0 ; i< 5;i++){
            sleep(2);
            sem_wait(&shm->sem);
            printf("\nP The current value of a is : %d\n",shm->a);
            shm->a = shm->a +2;
            sleep(1);
            printf("P changed the value of a: %d\n",shm->a);
            sem_post(&shm->sem);
        }
        wait(NULL);
        printf("\nFinal value of a: %d\n",shm->a);
    }
    return 0;
}