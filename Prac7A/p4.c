#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int arr[100];
int count = 0;//keeps a record of number of times a is found.
int a; //element to be searched;
void *linSearch(void *vargp)
{
    int i = (int)vargp;
    for(int j = 100*i; j< 100*(i+1); j++){
        if(a == arr[j]){
            printf("Element %d found at %dth index\n",a ,j);
            count++;
        }
    }
}

int main()
{
    int i;
    pthread_t tid;
    printf("The array elements are : \n");
    for(int i = 0 ; i < 100 ; i++){
        arr[i] = rand()%100;
        printf("%d ",arr[i]);
    }
    printf("\nEnter the int to be searched in the array: ");
    scanf("%d",&a);
    // Creating threads
    for (i = 0; i < 10; i++)
        pthread_create(&tid, NULL, &linSearch, (void *)i);
    pthread_join(&tid, NULL);
    if(count == 0)
        printf("\nElement not found!!!");
    return 0;
}