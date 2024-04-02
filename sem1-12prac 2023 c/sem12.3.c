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
   // if(argc != 5) {perror("args error\n"); exit(1);}
    FILE *file = fopen(argv[3], "r");
    key_t key = ftok(argv[1], atoi(argv[2]));
    int semid = semget(key, 3, IPC_CREAT | 0666);
    int n = atoi(argv[4]);
    struct sembuf semops;
    pid_t pid = getpid();
    semops.sem_num = 0;
    semops.sem_op = 1;
    semop(semid, &semops, 1);
    semops.sem_num = 2;
    semops.sem_op = -1;
    semop(semid, &semops, 1);
    char *s = malloc(1024);
    if(fgets(s, 1024, file) != NULL)
            printf("%s\n", s);
    free(s);
    fclose(file);
    return 0;
}