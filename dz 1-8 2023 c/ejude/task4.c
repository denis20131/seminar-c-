#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[]) 
{
    if (argc!=6) return 0;
    int fd[2];
    pipe(fd);
    pid_t pid1=fork();
    if (pid1==0)
        {
            close(fd[0]);
            dup2(fd[1],1);
            close(fd[1]);
            pid_t pid2=fork();
            if (pid2==0)
                {
                    int f1=open(argv[4],O_RDONLY);
                    dup2(f1,0);
                    close(f1);
                    execlp(argv[1],argv[1],NULL);
                    exit(1);
                }
            int status;
            waitpid(pid2,&status,0);
            if ((WIFEXITED(status)) && (!WEXITSTATUS(status)))
                {
                    pid_t pid3=fork();
                    if (pid3==0)
                        {
                            execlp(argv[2],argv[2],NULL);
                            exit(0);
                        }
                    wait(0);
                }
            exit(0);
        }
    close(fd[1]);
    pid_t pid4=fork();
    if (pid4==0)
        {
            dup2(fd[0],0);
            close(fd[0]);
            int f2=open(argv[5],O_CREAT|O_APPEND|O_WRONLY);
            dup2(f2,1);
            close(f2);
            execlp(argv[3],argv[3],NULL);
            exit(0);
        }
    close(fd[0]);
    wait(0);
    wait(0);
    return 0;
}