#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int c =0;
void handler1(int sig){
    signal(SIGINT, handler1);

    c++;
    printf("\nHANDLER %d\n", c);
    sleep(5);
}

void handler2(int sig){
    signal(SIGTSTP, handler2);
    printf("\nCtrl Z\n");
    exit(0);
}

int main(){
    signal(SIGTSTP, handler2);
    signal(SIGINT, handler1);
    while(1){
        pause();
    }
    return 0;
}


