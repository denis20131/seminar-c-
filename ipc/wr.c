#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#define SHMKEY 1234
#define SEMKEY 5678
#define writer_semaphore 1
#define read_semaphore 0
#define count_read 2
// Объявление глобальных переменных
struct sembuf decrease_read = {read_semaphore, -1, 1};
struct sembuf increase_read = {read_semaphore, 1, 1};
struct sembuf decrease_write = {writer_semaphore, -1, 1};
struct sembuf increase_write = {writer_semaphore, 1, 1};

typedef struct
{
    int command;
    char text[1024]; //сообщенеи передаваемое всем процессам
} Shared_memory;
Shared_memory *mem;
int shmid, semid;

    void hand(int s)
    {
        mem->command=0;
        shmdt(mem);
        // Удаление разделяемой памяти и семафора
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, read_semaphore, IPC_RMID);
        printf("\nprorams succes\n");
        exit(0);
    }



// Функция "писатель"
void writer() 
{
    sleep(2);
    printf("Писатель: Введите строку для записи в разделяемую память: ");
    fgets(mem->text,1024,stdin);
}

int main() {
    // Создание/получение идентификатора разделяемой памяти
    if ((shmid = shmget(SHMKEY, sizeof(Shared_memory), IPC_CREAT | 0666)) < 0) {
        perror("Ошибка: Не удалось получить идентификатор разделяемой памяти");
        exit(1);
    }

    // Получение указателя на разделяемую память
    if ((mem = shmat(shmid, NULL, 0)) == (void *) -1) {
        perror("Ошибка: Не удалось получить указатель на разделяемую память");
        exit(1);
    }

    // Создание/получение идентификатора семафора
    if ((semid = semget(SEMKEY, 2, IPC_CREAT | 0666)) < 0) {
        perror("Ошибка: Не удалось получить идентификатор семафора");
        exit(1);
    }
    mem->command=1;
    signal(SIGINT,hand);
    semctl(semid,writer_semaphore,SETVAL,1);
    while(1)
    {
    semop(semid,&decrease_write,1);
    writer();
    semctl(semid,read_semaphore,SETVAL,count_read);
    }
}