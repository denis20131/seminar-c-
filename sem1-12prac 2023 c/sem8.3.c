#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    if (argc < 6)
        return 1;

    int pipefd[2];
    pipe(pipefd);

    pid_t pid1, pid2;

    if ((pid1 = fork()) == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);

        execlp(argv[1], argv[1], argv[2], NULL);

        perror("Error while executing 1 command");
        _exit(1);
    }
    else if (pid1 < 0)
    {
        perror("Error while forking");
        _exit(1);
    }

    if ((pid2 = fork()) == 0)
    {
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        close(pipefd[1]);

        int file = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file == -1)
        {
            perror("Failed to open output file.");
            _exit(1);
        }

        dup2(file, 1);

        execlp(argv[3], argv[3], argv[4], NULL);
        perror("Error while executing 1 command");

        _exit(1);
    }
    else if (pid2 < 0)
    {
        perror("Error while forking");
        _exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}