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
    int N;
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
    ShmPtr = (struct Memory *)shmat(shmId, NULL, 0);

    // while (ShmPtr->done == 0)
    // {
    //     sleep(1);
    // }
    
    // Open a file named "outfile.txt" for writing.
    FILE *file = fopen("outfile.txt", "w");
    int temp, temp2;
    for (int i = (ShmPtr->N) - 1; i >= 0; i--)
    {
        temp = i;
        for (int j = i - 1; j >= 0; j--)
        {
            if (ShmPtr->data[j] > ShmPtr->data[temp])
            {
                temp = j;
            }
        }
        temp2 = (ShmPtr->data[temp]);
        (ShmPtr->data[temp]) = ShmPtr->data[i];
        ShmPtr->data[i] = temp2;
    }

    for (int i = 0; i < ShmPtr->N; i++)
    {
        fprintf(file, "%d\n", ShmPtr->data[i]);
    }

    // Close the file.
    fclose(file);
    shmdt((void *)ShmPtr);
    shmctl(shmId, IPC_RMID, NULL);
    printf("The integers in array have been sorted and printed in outfile.txt\n");
    return 0;
}