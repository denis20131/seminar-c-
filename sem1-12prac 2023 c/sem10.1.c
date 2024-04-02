#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void handler1(int sig)
{
    static int c =0;
    c++;
    if (c==2)
        {
            signal(SIGINT,SIG_DFL);
        }

}

int main()
{
    signal(SIGINT, handler1);
    while(1)
        pause();
    return 0;
}
