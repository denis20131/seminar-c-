#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int execute_command(char *command) 
{
    pid_t pid = fork();
    
    if (pid < 0) 
    { 
        perror("fork");
        return 1;
    } 
    else 
    if (pid == 0) 
        { 
            execlp(command, command, NULL);
            perror("execlp");
            exit(1);
        } 

    else 
    
        { 
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) 
                {
                    if (WEXITSTATUS(status) == 0) 
                        return 0;
                    else 
                        return 1;
                } 
            else 
                    return 1;
        }
}

int main(int argc, char *argv[]) 
{
    if (argc != 4) 
        return 1;

    char *cmd1 = argv[1];
    char *cmd2 = argv[2];
    char *cmd3 = argv[3];
    return !((((execute_command(cmd1))==0) || ((execute_command(cmd2))==0)) && ((execute_command(cmd3))==0));
}