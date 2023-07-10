#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    int *shared; /* pointer to the shm */
    int shmid;
    shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    printf("Shared Memory ID=%u\n", shmid);
    if (fork() == 0)
    { /* Child */
        /* Attach to shared memory and print the pointer */
        shared = shmat(shmid, (void *)0, 0);
        printf("Child pointer %u\n",*shared);
        *shared = 1;
        printf("Child value=%d\n", *shared);
        sleep(2);
        printf("Child value=%d\n", *shared);
    }
    else
    { /* Parent */
        /* Attach to shared memory and print the pointer */
        shared = shmat(shmid, (void *)0, 0);
        printf("Parent pointer %u\n",*shared);
        printf("Parent value=%d\n", *shared);
        sleep(1);
        *shared = 42;
        printf("Parent value=%d\n", *shared);
        sleep(5);
        shmctl(shmid, IPC_RMID, 0);
    }
}