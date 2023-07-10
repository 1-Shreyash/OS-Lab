#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void compute_max(int *a, int l, int r)
{
    // If the chunk is small, compute the maximum directly.
    if (r - l < 10)
    {
        int max = a[l];
        for (int i = l + 1; i <= r; i++)
        {
            if (a[i] > max)
            {
                max = a[i];
            }
        }
        exit(max);
    }

    // Otherwise, create two child processes to handle the left and right halves of the chunk.
    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        compute_max(a, l, (l + r) / 2);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        compute_max(a, (l + r) / 2 + 1, r);
    }

    // Wait for the child processes to exit.
    int max1, max2;
    waitpid(pid1, &max1, 0);
    waitpid(pid2, &max2, 0);
    max1 = max1 >> 8;
    max2 = max2 >> 8;

    // Return the maximum of the two maximum values.
    int max = max1 > max2 ? max1 : max2;
    printf("The max of chunk is %d, Child id: %d, Parent id: %d\n",max ,getpid() ,getppid() );
    exit(max);
}
int main()
{
    int n = 50;

    // Create an array of size n.
    int a[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 128;
    }

    // Print the array.
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    // Create the root process.
    pid_t pid = fork();
    if (pid == 0)
    {
        // The root process recursively computes the maximum.
        compute_max(a, 0, n - 1);
    }
    // Wait for the root process to exit.
    int status;
    wait(&status);
    printf("Maximum is : %d",status>>8);

    return 0;
}
