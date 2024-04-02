#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define N 100
int main(int argc, char **argv)
{
    int fd[2];
    int fd1[2];
    pipe(fd);       
    char buf[N];
    FILE *f=fopen(argv[1],"r+");
            if (!f) 
                {
                    fprintf(stderr,"error",1);
                    exit(5);
                }
    int pos=ftell(f);
    while (fgets(buf,N,f))
        {
            write(fd[1],buf,strlen(buf)+1);
            read (fd1[0],buf,N);
            fseek(f,pos,SEEK_SET);
        }
    pid_t pid1,pid2;
    if ((pid1=fork)==0)
        {
            close(fd[1]);
            while(read(fd[0],buf,N))
                {
                    rewrite(buf);
                    write(fd[0],buf,strlen(buf)+1);
                }
            close(fd[0]);
            close(fd1[0]);
            close(fd1[1]);

        ;}
    else
        {
            fprintf(stderr,"error",1);
            exit(5);
        }
    return 0;
}