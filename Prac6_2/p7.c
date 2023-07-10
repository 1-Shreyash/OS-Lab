#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int p1[2], p2[2], n, pid;
    int c, d;
    pipe(p1);
    pipe(p2);
    int s = 0;
    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        perror("Fork creation failed!!");
    }
    else if (pid1 == 0)
    {
        pid_t pid2 = fork();
        if (pid2 < 0)
        {
            perror("Fork creation failed!!");
        }
        else if (pid2 == 0)
        { // Child C
            // printf("PROCESS C\n");
            rand();
            while (s == 0)
            {
                int n = rand();
                // printf("%d\n",n);
                write(p1[1], &n, sizeof(int));
            }
        }
        else
        { // Child D
            // printf("PROCESS D\n");
            while (s == 0)
            {
                int n = rand();
                // printf("%d\n",n);
                write(p2[1], &n, sizeof(int));
            }
        }
    }
    else if (pid1 > 0)
    { // Parent Process
        printf("\n\n🔥🔥🔥🔥🔥🔥🔥🔥GAME STARTS🔥🔥🔥🔥🔥🔥🔥🔥\n\n");
        int tpoints = 0;
        int Cpoint = 0, Dpoint = 0;
        while (Cpoint < 10 && Dpoint < 10)
        {
            int c, d;
            int flag;
            int n1 = read(p1[0], &c, sizeof(int));
            int n2 = read(p2[0], &d, sizeof(int));
            int n = rand() % 2;
            if (n == 0)
            { // choose Max
                printf("\t##### CHOSEN MAX ####\n");
                printf("\tc : %d, d : %d\n",c,d);
                if (c > d)
                {
                    Cpoint += 1;
                    printf("\tC WON!!!\n");
                }

                else if (c < d)
                {
                    Dpoint += 1;
                    printf("\tD WON!!!\n");
                }
                else
                    printf("\tTie\n");
                printf("\tC score: %d\n", Cpoint);
                printf("\tD score: %d\n", Dpoint);
                printf("\n\n");
            }
            else
            { // choose Min
                printf("\t##### CHOSEN MIN ####\n");
                printf("\tc : %d, d : %d\n",c,d);
                if (c > d)
                {
                    Dpoint += 1;
                    printf("\tD WON!!!\n");
                }

                else if (c < d)
                {
                    Cpoint += 1;
                    printf("\tC WON!!!\n");
                }
                else
                    printf("\tTie\n");
                printf("\tC score: %d\n", Cpoint);
                printf("\tD score: %d\n", Dpoint);
                printf("\n\n");
            }
        }
        s = 1;
        if(Cpoint==10)
            printf("!!!! C WON !!!! 🥳");
        else if(Dpoint==10)
            printf("!!!! D WON !!!! 🥳");
    }
}