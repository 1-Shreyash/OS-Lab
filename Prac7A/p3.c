#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int mat1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int mat2[3][3] = {{1, 1, 0}, {0, 0, 1}, {1, 0, 0}};
int mat3[3][3];


void *matMul(void *vargp)
{
    int i = (int)vargp;
    for (int k = 0; k < 3; k++)
    {
        int sum = 0;
        for (int j = 0; j < 3; j++)
        {
            sum += mat1[i][j] * mat2[j][k];
        }
        mat3[i][k] = sum;
    }
}

int main()
{
    int i;
    pthread_t tid;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat3[i][j] = 0;
        }
    }
    // Creating threads
    for (i = 0; i < 3; i++)
        pthread_create(&tid, NULL, &matMul, (void *)i);
    pthread_join(&tid, NULL);
    

    printf("Matrix A: \n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", mat1[i][j]);
        }
        printf("\n");
    }
    printf("Matrix B: \n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", mat2[i][j]);
        }
        printf("\n");
    }
    
    //printing the matrix:
    printf("Their multiplication is : \n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", mat3[i][j]);
        }
        printf("\n");
    }
    return 0;
}