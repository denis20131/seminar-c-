#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/file.h>

#define MAXLEN 10

int flag = 1;

void heandler_al(int sig){
    
        // printf("%d\n", getppid());
        kill(getppid(), SIGUSR2);
        exit(0);

}
void heandler(int sig){
}
void heandler2(int sig){
    flag = 0;
    
}

char* read_word(int fd){
    char* str = NULL;
    char c;
    int i = 0;
    while(read(fd, &c, 1)>0){
        if(!str){str = (char*)malloc(MAXLEN);}
        if(c=='\n'){
            str[i] = '\0';
            break;
        }
        else{
            str[i] = c;
        }
        i++;
    }
    return str;
}

int main(int argc, char** argv){
    if(argc!=2) return 1;
    int fd = open(argv[1], O_RDONLY);
    if(fd < 0) return 0;

    signal(SIGUSR1, heandler);
    int son = 1;
    if(!(son=fork()))
    {
        signal(SIGALRM, heandler_al);
        kill(getppid(), SIGUSR1);
        alarm(4);
        char* buf;
        while(1)
        {
            pause();
            if(!(buf=read_word(fd))){close(fd);raise(SIGALRM);}
            printf("SON %s\n", buf);
            fflush(stdout);
            free(buf);
            kill(getppid(), SIGUSR1);
        }
    }
    else{
        
        signal(SIGUSR2, heandler2);
        char* buf;
        while(flag)
        {
            pause();
            buf=read_word(fd);
            if(buf){printf("Father %s\n", buf);}
            free(buf);
            kill(son, SIGUSR1);
        }
        close(fd);
        printf("\n");
        while(1)
        {
            printf("Father\n");
            fflush(stdout);
            sleep(1);
        }
    }

    return 0;
}
