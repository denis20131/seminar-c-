#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sig){
    signal(SIGINT, handler);
}

int main(){
    
    pid_t pid1;
    if(!(pid1=fork())){
        printf("SON: %d\n", getpid());
        while(1){}
    }

    
    signal(SIGINT, handler);
    printf("FATHER: %d\n", getpid());
    int id; 
    printf("\n%d\n", waitpid(pid1, &id, 0));

    return 0;
}