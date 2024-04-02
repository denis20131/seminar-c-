#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int flag = 1;

void heandler_al(int sig)
{
        kill(getppid(), SIGUSR2); //сигнал отцу
        exit(0); //завершение сына

}
void heandler(int sig)
{
}
void heandler2(int sig)
{
    flag = 0;
}

int main()
{
    
    signal(SIGUSR1, heandler);
    int son;
    if(!(son=fork()))
    {
        signal(SIGALRM, heandler_al);
        kill(getppid(), SIGUSR1);
        alarm(2);
        while(1)
        {
            pause();
            printf("SON ");
            fflush(stdout);
            kill(getppid(), SIGUSR1);
        }
    }
    else
    {
        
        signal(SIGUSR2, heandler2);
        while(flag) 
        {
            pause();
            printf("Father ");
            fflush(stdout);
            kill(son, SIGUSR1);
        }
        printf("\n");
        while(1)
        {
            printf("Father\n");
            sleep(1);
        }
    }

    return 0;
}
