#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(){
    pid_t pid = fork();
    int fd, charcount;
    char buf[100];
    if(pid==0){
        fd = creat("Relation.txt",0777);
        printf("File created !!!\n");
    }
    else if(pid > 0){
        wait(NULL);
        fd = open("Relation.txt", O_WRONLY|O_APPEND, 0777);
        printf("File opened.\n");
        printf("Enter the contents to write to the file: ");
        scanf("%s",buf);
        charcount = strlen(buf);
        write(fd, buf, charcount);
        close(fd);
    }
    else{
        printf("Fork creation failed\n");
    }
}