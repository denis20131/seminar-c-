#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    struct{
        long mtype;
        int n;
    }msg;
    if (argc!=5)
    {
        return 0;
    }
    char symb = argv[2][0];
    key_t key = ftok(argv[1],symb);
    int mesid = msgget(10,IPC_CREAT|0666);

    int fd = open(argv[3],O_WRONLY|O_APPEND|O_TRUNC);
    
    int N = atoi(argv[4]);
    for (int i=0;i<N;i++)
    {   
        char *s;
        s = calloc(1000,1);
        sprintf(s,"%d %d\n",getpid(),i);
        write(fd,s,strlen(s));
        free(s);
        msg.mtype = 1;
        msg.n = 1;
        msgsnd(mesid,&msg,sizeof(int),0);
        msgrcv(mesid,&msg,sizeof(int),3,0);
    }
    msgctl(mesid,IPC_RMID,0);
    close(fd);
    exit(0);
}