#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    int fd[2],fd2[2],fd3[2];int buf;
    pipe(fd);pipe(fd2);
    pid_t pid1=fork();
    if (pid1==0) 
        {int m1,m2;read(fd[0],&buf,4);
            write(fd2[1],&buf,4);
            read(fd[0],&buf,4);
            read(fd[0],&m2,4);
            printf("pid2: %d      vnuk1:%d  vnuk2: %d \n",buf,m1,m2);
            buf=getpid();
            write(fd2[1],&buf,4);
            write(fd2[1],&buf,4);
            close(fd[0]);
            close(fd2[1]);
            exit(0);}
    pid_t pid2=fork();
    if (pid2==0)
        {
            int buf=getpid();
            write(fd[1],&buf,4);
            pid_t pid21=fork();
            if (pid21==0) 
                {int m=getpid();
                write(fd[1],&m,4);
                printf("vnuk1:%d\n",getpid());
                read(fd2[0],&buf,4);
                printf("son1: %d\n",buf);
                exit(0);};
            wait(NULL);
            pid_t pid22=fork();
            if (pid22==0) 
                {
                    int m=getpid();
                    write(fd[1],&m,4);
                    printf("vnuk2:%d\n",getpid());
                    read(fd2[0],&buf,4);
                    printf("son1: %d\n",buf);
                    exit(0);};
            close(fd2[0]);
            close(fd[1]);
            wait(NULL);
            exit(0);
        }
    wait(NULL);
    wait(NULL);
    return 0;
}