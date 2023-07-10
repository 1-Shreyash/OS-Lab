#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define SIZE 100

pthread_t tid[SIZE/10];
int a[SIZE];

int maxi = 0;
int min = INT8_MAX;

void MaxMin(void *i){
    int k = (int) i;
    for(int j= k*10; j< (k+1)*10;j++){
        if(a[j]>maxi)
            maxi = a[j];
        if(a[j]<min)
            min = a[j];
    }
}
int main()
{
    printf("The array elements are:\n");
    // initialising 100 variables
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 1000;
        printf("%d ", a[i]);
    }
    printf("\n");
    int i = 0;
    int err;
    while (i < 10)
    {
        err = pthread_create(&(tid[i]), NULL, &MaxMin, (void *) i);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    i = 0;
    while (i < 10){
        pthread_join (&(tid[i]) ,NULL);
        i++;
    }
    printf("The maximum value is: %d\n",maxi);
    printf("The minimum value is: %d\n",min);
    return 0;
}