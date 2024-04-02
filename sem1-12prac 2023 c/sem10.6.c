#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

int n;

void handler_c(int sig){
    signal(SIGINT, handler_c);
    static int count = 0;
    n -= 4;
    count++;
    printf("\nSIGINT %d %d\n", count, n);
    if(n<0){exit(0);}    
}

void handler_z(int sig){
    signal(SIGTSTP, handler_z);
    static int count = 0;
    n += 3;
    count++;
    printf("\nSIGTSTP %d %d\n", count, n);
}

int main(int argc, char** argv){
    signal(SIGINT, handler_c);
    signal(SIGTSTP, handler_z);
    n = atoi(argv[1]);

    while(1){
        pause();
    }

    return 0;
}