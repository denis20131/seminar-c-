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
    FILE *f = fopen(argv[3],"r");
    for (int i=0;i<N;i++)
    {   
        msgrcv(mesid,&msg,4,2,0);
        char s[50];
        fgets(s,50,f);
        printf("%s",s);
        fgets(s,50,f);
        printf("%s",s);
        msg.mtype = 3;
        msgsnd(mesid,&msg,4,0);
    }
    msgctl(mesid,IPC_RMID,0);

    exit(0);
}