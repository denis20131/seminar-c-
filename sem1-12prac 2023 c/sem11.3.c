#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
pid_t pid;

char c = 0;
int bitIndex = 7;
void first(int status)
{
    c |= ((status == SIGUSR2) << bitIndex);

    bitIndex--;
    if (bitIndex < 0)
    {
        printf("%c", c);
        c = 0;
        bitIndex = 7;
    }

    kill(pid, SIGALRM);
}

void child_exit(int status)
{
    _exit(0);
}

void Handler(int status){};

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    signal(SIGUSR1, first);
    signal(SIGUSR2, first);
    signal(SIGALRM, Handler);
    signal(SIGIO, child_exit);

    if ((pid = fork()) == 0)
    {
        while (1)
            pause();
        exit(0);
    }

    if (fork() == 0)
    {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            return 1;

        int len;
        while (read(fd, &c, sizeof(char)))
        {
            for (int i = 7; i >= 0; i--)
            {
                int bit = (c >> i) & 1;

                kill(pid, bit ? SIGUSR2 : SIGUSR1);
                pause();
            }
        }

        kill(pid, SIGIO);
        close(fd);
        exit(0);
    }

    wait(0);
    wait(0);
}