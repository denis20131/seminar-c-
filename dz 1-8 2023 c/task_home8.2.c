#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main() 
{
int channel[2];

if (pipe(channel) == -1) 
    {
    perror("Ошибка создания канала");
    exit(1);
    }

pid_t child_pid,grandchild_pid,great_grandchild_pid;

if ((child_pid=fork()) == -1) 
    {
    perror("Ошибка создания процесса-сына");
    exit(1);
    }

if (child_pid == 0) 
    {
            if ((grandchild_pid=fork()) == -1) 
                {
                perror("Ошибка создания процесса-внука");
                exit(1);
                }
            else 
                if (grandchild_pid == 0) 
                    { 
                            if ((great_grandchild_pid=fork()) == -1) 
                                    {
                                    perror("Ошибка создания процесса-правнука");
                                    exit(1);
                                    }
                            else
                                if (great_grandchild_pid==0)
                                    {
                                        close(channel[0]);
                                        time_t current_time = time(NULL);
                                            write(channel[1],&current_time,sizeof(time_t));
                                            write(channel[1],&current_time,sizeof(time_t));
                                            write(channel[1],&current_time,sizeof(time_t));
                                        close(channel[1]);
                                        exit(0);
                                    }
                            close(channel[1]);
                            wait(NULL);
                            time_t current_time = time(NULL);
                            read(channel[0], &current_time, sizeof(time_t));
                            struct tm* time_info;
                            time_info = localtime(&current_time);
                            int day = time_info->tm_mday;
                            printf("D:%02d\n", day);
                            close(channel[0]);
                            exit(0);
                    }
                
                else 

                    {
                    close(channel[1]);
                    wait(NULL); 
                    time_t current_time;
                    read(channel[0], &current_time, sizeof(time_t));
                    struct tm* time_info;
                    time_info = localtime(&current_time);
                    int month = time_info->tm_mon+1;
                    printf("M:%02d\n", month);
                    close(channel[0]);
                    exit(0);
                    }
}

else 
    {
        close(channel[1]);
        wait(NULL);
        time_t current_time;
        read(channel[0], &current_time, sizeof(time_t));
        struct tm* time_info;
        time_info = localtime(&current_time);
        int year = time_info->tm_year + 1900;
        printf("Y:%d\n", year);
        close(channel[0]);
        exit(0);
    }
}