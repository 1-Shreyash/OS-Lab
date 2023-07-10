#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 1000000
int main()
{
    clock_t start, end;
    start = clock();
    int a[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 1000;
        // printf("%d ", a[i]);
    }
    int max = a[0], min = a[0];
    for (int i = 0; i < SIZE; i++)
    {
        if (a[i] > max)
            max = a[i];
        if (a[i] < min)
            min = a[i];
    }
    end = clock();
    printf("\nThe max value is: %d\n", max);
    printf("The min value is: %d\n", min);
    printf("Time diff = %lu", end - start);
}