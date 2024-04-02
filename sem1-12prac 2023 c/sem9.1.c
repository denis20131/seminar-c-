#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    pid_t pid1,pid2;
    if ((pid1=fork())==0)
        {
            dup2(fd[1],1);
            close(fd[0]);
            close(fd[1]);
            execlp(argv[1],argv[1],NULL);
            perror("1");exit(1);
        }
    else if (pid1<0)
            { printf("ERROR fork");
             exit(1);}
    else
        {
            if (pid2=fork()==0)
            {
            dup2(fd[0],0);
            close(fd[1]);
            close(fd[0]);
            execlp(argv[2],argv[2],NULL);
            perror("2");exit(2);
            }
            else if (pid2<0) {printf("error");exit(5);}
            else    
                {
                  int status;
                  waitpid(pid2,&status,0);
                  char buf;
                  while(read(fd[0],&buf,sizeof(char)))
                        printf("%c",buf);
                close(fd[0]);
                wait(0);
                return 0;
        }
}
}