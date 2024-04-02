#include <stdio.h>
#include <unistd.h>
#include <wait.h>
int main()
{
    int N;
    scanf("%d",&N);

    for (int i=1;i<=N;i++)
    {
        pid_t pid;
        printf("%d",i);
        if (i!=N) printf(" ");
        fflush(stdout);
        if ((pid=fork())==0)
        {
            continue;
        }
        waitpid(pid,0,0);
        return 0;
    }
   printf("\n");
    return 0;
}
