#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int f1=open(argv[2],O_RDONLY,0666);
    if (f1==-1)
        {
            printf("error");
            return 0;
        }
    int f1_tmp;
    int fd[2];
    pipe(fd);
    pid_t pid1,pid2,po;
    if (pid1=fork()<0) {printf("error fork");exit(3);}
    else if (pid1==0) 
        {
            dup2(f1,0);
            close(f1);
            dup2(fd[1],1);
            close(fd[0]);
            close(fd[1]);
            execlp(argv[1],argv[1],NULL);
            printf("%s aborted exit(%d)",argv[1],1);
            exit(1);
        }
    else    
        {
            int status;
            waitpid(pid1,&status,0);
            if (!status)
                {
                    if (pid2==fork()<0) {printf("error fork");exit(1);}
                    if (pid2==0)
                        {
                            dup2(fd[1],1);
                            close(fd[1]);
                            close(fd[0]);
                            execlp(argv[3],argv[3],NULL);
                            printf("%s aborted exit(%d)",argv[3],2);exit(0);
                        }
                }
        }
    pid_t pid3=fork();
    if (!pid3)
        {
                dup2(fd[0],0);
                close(fd[0]);close(fd[1]);
                int f2=open(argv[5],O_RDWR,O_CREAT,0666);
                dup2(f2,1);
                execlp(argv[4],argv[4],NULL);
                perror("3");exit(1);
        }
    close(fd[0]);
    close(fd[1]);
    wait(0);
    wait(0);

    return 0;
}