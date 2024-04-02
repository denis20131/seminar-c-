#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig)
{
    signal(SIGINT, handler);
    printf("\nHandler: %d\n",  getpid());
    exit(0);
}

int main()
{
    signal(SIGINT, handler);
    printf("%d\n", getpid());
    pid_t pid1;
    if(!(pid1=fork()))
        while(1);
    kill(0, SIGINT);
    return 0;
}