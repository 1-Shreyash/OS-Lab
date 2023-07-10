#include <unistd.h>
#include <stdio.h>
int main()
{
    int pid, pip[2];
    char instring[20];
    pipe(pip);
    pid = fork();
    if (pid == 0) /* child : sends message to parent*/
    {
        /* send 7 characters in the string, including end-of-string */
        write(pip[1], "Hi Mom!", 8);
    }
    else /* parent : receives message from child */
    {
        /* read from the pipe */
        read(pip[0], instring, 9);
        printf("%s",instring);
    }
    return 0;
}