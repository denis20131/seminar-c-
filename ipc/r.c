#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#define SHMKEY 1234
#define SEMKEY 5678
#define writer_semaphore 1
#define read_semaphore 0
struct sembuf decrease_read = {read_semaphore, -1,1};
struct sembuf increase_read = {read_semaphore, 1,1};
struct sembuf decrease_write = {writer_semaphore, -1,1};
struct sembuf increase_write = {writer_semaphore, 1,1};


typedef struct
{
    int command;
    char text[1024]; //сообщенеи передаваемое всем процессам
} Shared_memory;

int main() {
    Shared_memory *mem;
    int shmid, semid;
    // Создание/получение идентификатора разделяемой памяти
    if ((shmid = shmget(SHMKEY, sizeof(Shared_memory), 0)) < 0) {
        perror("Ошибка: Не удалось получить идентификатор разделяемой памяти");
        exit(1);
    }

    // Получение указателя на разделяемую память
    if ((mem = shmat(shmid, NULL, 0)) == (void *) -1) {
        perror("Ошибка: Не удалось получить указатель на разделяемую память");
        exit(1);
    }

    // Создание/получение идентификатора семафора
    if ((semid = semget(SEMKEY,2,0)) < 0) {
        perror("Ошибка: Не удалось получить идентификатор семафора");
        exit(1);
    }

    // Процесс-читатель
    while(mem->command) //пока основной процесс не закончится
    {
        semop(semid, &decrease_read, 1);
        printf("Чтение строки из разделяемой памяти: %s\n", mem->text);
        //scanf("%d",&mem->command);
        //if (mem->command==0) semop(semid, &increase_write, 1);
        semop(semid,&increase_write,1);
    }
    shmdt(mem);
    return 0;
}