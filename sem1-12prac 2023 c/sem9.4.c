#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define LEN 100

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        perror("Insufficient arguments");
        exit(1);
    }

    int file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1)
    {
        perror("Error opening file!");
        exit(1);
    }

    int fd[2], fd1[2];
    pipe(fd);
    pipe(fd1);

    if (fd == -1 || fd1 == -1)
    {
        perror("Failed to open pipes");
        exit(1);
    }

    pid_t pid1;
    if ((pid1 = fork()) == 0)
    {
        close(fd[1]);
        close(fd1[0]);

        char c;
        char buf[LEN];
        while (1)
        {
            if (read(fd[0], &c, 1) <= 0 || read(fd[0], buf, LEN) <= 0)
                break;

            int count = 0;
            for (int i = 0; i < strlen(buf); i++)
                if (buf[i] == c)
                    count++;

            dprintf(file, " %d\n", count);

            write(fd1[1], &count, 4); 
        }

        close(fd[0]);
        close(fd1[1]);

        exit(0);
    }

    if (pid1 == -1)
    {
        perror("Error while forking!");
        exit(1);
    }

    char c;
    char buf[LEN];

    close(fd[0]);
    close(fd1[1]);
    while (scanf("%c", &c) == 1 && scanf("%s", &buf) == 1 && strcmp(buf, "exit") != 0)
    {
        dprintf(file, "%s", buf);

        write(fd[1], &c, 1);
        write(fd[1], buf, sizeof(buf));

        read(fd1[0], NULL, 4);

        fflush(stdin);
    }

    close(fd[1]);
    close(fd1[0]);

    close(file);
}