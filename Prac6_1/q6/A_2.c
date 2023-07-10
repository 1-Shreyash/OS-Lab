#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct Memory
{
    int N, done;
    int data[100];
} Mem;

int main()
{
    Mem m;
    key_t key;
    int shmId, i;
    Mem *ShmPtr;
    key = 345;
    shmId = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666);
    ShmPtr = (Mem *)shmat(shmId, NULL, 0);

    ShmPtr->done = 0;

    // Open the file inpfile for reading.
    FILE *fp = fopen("inpfile.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file inpfile.\n");
        return 1;
    }
    ShmPtr->N = 0;

    // Read the integers from the file.
    while (fscanf(fp, "%d", &(ShmPtr->data[(ShmPtr->N)])) == 1)
    {
        (ShmPtr->N)++;
    }
    fclose(fp);

    // ShmPtr->data[1] = 112;
    // Print the integers.
    printf("The integers in saved from inpfile.txt file to the array:\n");
    for (int i = 0; i < ShmPtr->N; i++)
    {
        printf("%d ", ShmPtr->data[i]);
    }

    ShmPtr->done = 1;
    return 0;
}
