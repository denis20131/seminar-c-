#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
 {
    printf("Родительский процесс: Сыновий процесс с PID завершился\n");
}

int main() {
    // Установка обработчика сигнала SIGCHLD
    signal(SIGCHLD, handler);
    pid_t child_pid = fork();

    if (child_pid == 0) {
        sleep(3);
    } else {
        printf("Родительский процесс: Создан сыновий процесс с PID %d\n", child_pid);
        sleep(5);
        system("ps a");
    }
    return 0;
}