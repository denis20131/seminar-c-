#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig){}


int main(int argc, char** argv)
{
    if(argc!=4)
        {
            printf("error count arguments\n"); 
            exit(0);
        }
    
    int N= atoi(argv[1]);
    if (N<=1)
        {
            printf("error N\n");
            exit(0);
        }
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    if (start>=end)
        {
            printf("start>=end\n");
            exit(0);
        }

    int ind = -1;
    int fd[2];

    if (pipe(fd)==-1)
        {
            printf("error pipe\n");
            exit(0);
        }

    signal(SIGUSR1, handler);

    int pids[N];
    pids[0] = getpid();

    for(int i=1; i<N; i++)
        {
            if((pids[i]=fork())<0)
                {
                    printf("error fork\n");
                    exit(0);
                }

            if(pids[i]==0)
                {
                    ind = i;
                    write(fd[1], &i, 4);
                    break;
                }
        }

    if(ind > 0)
    {
        int k;
        while(1)
            {
                pause();
                read(fd[0], &k, 4);
                if(k > end)
                    {
                        write(fd[1], &k, 4);
                        kill(pids[0], SIGUSR1);
                        close(fd[0]); 
                        close(fd[1]);
                        exit(0);
                    }

                printf("номер процесса:%d  число:%d\n", getpid(), k);    
                k++;
                write(fd[1], &k, 4);
                kill(pids[0], SIGUSR1);
            }
        close(fd[0]); 
        close(fd[1]);
        exit(0);
    }
    else
        {
            int k;
            int check = 0;
            while(read(fd[0],&k, 4)>0)
            {
                check++;
                if(check==N-1) break;
            }
            k = start;
            int fl=1;
            while(1)
                {

                    for(int i=0; i<N; i++)
                        {
                            if(!i) 
                                {
                                    printf("номер процесса:%d  число:%d\n", pids[0], k);
                                    k++;
                                    continue;
                                }
                            kill(pids[i], SIGUSR1);
                            write(fd[1], &k, 4);
                            pause();
                            read(fd[0], &k, 4);

                            if(k > end)
                                {
                                    fl = 0;
                                    break;
                                }
                        }
                    if(!fl)
                        {
                            for(int i=1; i<N; i++)
                                {
                                    write(fd[1], &k, 4); 
                                    kill(pids[i], SIGUSR1); 
                                    waitpid(pids[i],0,0);
                                }
                            break;
                        }   
                }

            close(fd[0]); 
            close(fd[1]);
            exit(0);
        }
}