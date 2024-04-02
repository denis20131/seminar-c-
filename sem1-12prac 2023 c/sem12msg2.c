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
    int N = atoi(argv[4]);
    int fd = open(argv[3],O_WRONLY|O_APPEND);

    for (int i=0;i<N;i++)
    {   
        msgrcv(mesid,&msg,sizeof(int),1,0);
        char *s;
        s = malloc(50);
        sprintf(s,"%d MESSAGE\n",getpid());
        s = realloc(s,strlen(s));
        write(fd,s,strlen(s));
        free(s);
        msg.mtype = 2;
        msg.n = 1;
        msgsnd(mesid,&msg,sizeof(int),0);
    }
    close(fd);

    msgctl(mesid,IPC_RMID,0);
    exit(0);
}