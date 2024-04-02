
//kill
//kill -l увидим список сигналов
#include <fcntl.h>
#include <stdio.h>
#include<unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

void p(int) {signal(SIGALRM,p);}
void hendler(int sig)
    {
        signal(SIGINT,hendler);
    if (alarm(5)>0)
        {
            exit(0);
        }
    printf("x\n");
    }

int main()
{
    signal(SIGINT,hendler);
    signal(SIGALRM,p);
    while(1)
        {
            pause();
        }
}