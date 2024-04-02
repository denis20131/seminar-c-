#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char** argv)
{
    if(argc!=4)
        {   printf("error count arguments\n"); 
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

    int fd[N][2];
 
 for(int i=0;i<=N-1;i++)
    {
        if (pipe(fd[i])<0)
            {
                printf("error pipe\n");
                exit(0);
            }
    }

int pids[N-1];
for (int i=0;i<N-1;i++)

    {
            if((pids[i]=fork())< 0)
                {
                    printf("error fork\n");
                    exit(0);
                }

        else if (pids[i]==0)
            {   
                int count;
                for(int j=0;j<N; j++)
                    {
                        if(j==i)
                            {
                                close(fd[j][1]); 
                                continue;
                            }
                        if(j==(i+1)%N)
                            {   
                                close(fd[j][0]); 
                                continue;
                            }
                        close(fd[j][0]);
                        close(fd[j][1]);
                    }

                while (read(fd[i][0], &count, 4)>0)
                {
                    if(count > end)
                        {   
                            write(fd[(i+1)%N][1], &count, 4); 
                            break;
                        }
                    printf("номер процесса:%d  число:%d\n", getpid(), count);
                    count++;
                    write(fd[(i+1)%N][1], &count, 4);
                }
                
                close(fd[i][0]);
                close(fd[(i+1)%N][1]);
                exit(0);
            }
    }
    
    for(int i=1; i<N-1; i++)
    {
        close(fd[i][0]); 
        close(fd[i][1]);
    }

    close(fd[0][0]); 
    close(fd[N-1][1]);

int count = start;
printf("номер процесса:%d  число:%d\n", getpid(), count);
count++;
write(fd[0][1], &count, 4);

    while(read(fd[N-1][0], &count, 4)>0)
        {
            if(count > end) break;
            printf("номер процесса:%d  число:%d\n", getpid(), count);
            count++;
            write(fd[0][1], &count, 4);
        }

    close(fd[N-1][0]); 
    close(fd[0][1]);

    for (int i=0;i<N;i++)
        waitpid(pids[i],0,0);

    exit(0);
}
