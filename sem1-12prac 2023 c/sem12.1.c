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
    FILE *file = fopen(argv[3], "a");
    key_t key = ftok("a.out", "b");
    int semid = semget(key, 3, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 0);
    semctl(semid, 1, SETVAL, 0);
    semctl(semid, 2, SETVAL, 0);
    int n = atoi(argv[4]);
    struct sembuf semops;
    pid_t pid = getpid();
    for(int i = 1; i <= n; i++)
    {
        semops.sem_num = 0;
        semops.sem_op = -1;
        semop(semid, &semops, 1); //дожидаемся 3 файла
        fprintf(file, "%d %d\n", pid, i);
        fflush(file);

        semops.sem_num = 1;
        semops.sem_op = 1;
        semop(semid, &semops, 1);
    }
    fclose(file);

    semops.sem_num = 2;
    semops.sem_op = 1;
    semop(semid, &semops, 1);
    return 0;
}