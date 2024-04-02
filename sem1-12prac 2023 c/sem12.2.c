#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main(int argc, char** argv)
{
    if(argc != 5) {perror("args error\n"); exit(1);}
    FILE *file = fopen(argv[3], "a");
    key_t key = ftok(argv[1], atoi(argv[2]));
    int semid = semget(key, 3, IPC_CREAT | 0666);
    int n = atoi(argv[4]);
    struct sembuf semops;
    pid_t pid = getpid();
    for(int i = 1; i <= n; i++)
    {
        semops.sem_num = 1;
        semops.sem_op = -1;
        semop(semid, &semops, 1);
        fprintf(file, "%d kakoe-to soobschenie\n", pid);
        fflush(file);

        semops.sem_num = 0;
        semops.sem_op = 1;
        semop(semid, &semops, 1);
    }
    fclose(file);

    semops.sem_num = 2;
    semops.sem_op = 1;
    semop(semid, &semops, 1);
    return 0;
}