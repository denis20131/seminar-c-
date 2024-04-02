#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <string.h>
#include <sys/wait.h>

#define len 100

int main(int argc,char** argv)
{
    char str [len];
    __pid_t pid;
    FILE* file = fopen(argv[1], "w");
    if (!file) 
        {
                    perror("Error opening file!");
                    exit(1);
        }
    int fd[2];
    int ch = pipe(fd);
    int fd1[2];
    int ch1 = pipe(fd1);
    if (ch == -1 || ch1 == -1)
        {
            perror("Failed pipes");
            exit(1);
        }
    pid = fork();
    if(pid==0)
        {
        char c;
        close(fd[1]);
        close(fd1[0]);
            while(read(fd[0], &c, 1))
            {
                read(fd[0], str, len);
                if(strcmp(str, "exit")==0)
                    {
                        write(fd1[1], &c, 1); 
                        break;
                    }
                int l = strlen(str);
                int ans = 0;
                for(int i =0; i<l; i++)
                    if (str[i]==c) ans+=1;
                fprintf(file, " %d\n", ans);
                fflush(file);
                write(fd1[1], &c, 1);
            }
            close(fd1[1]);
            close(fd[0]);
            exit(0);
        }
    else if(pid<0){perror("exit fork"); exit(1);}
    else{
        char c;
        close(fd[0]);
        close(fd1[1]);
        while(1)
        {
            scanf("%c", &c);
            getchar();
            fgets(str, len, stdin);
            str[strcspn(str,"\n")] = '\0';
            fprintf(file ,"%s",str);
            write(fd[1], &c, 1);
            write(fd[1], str, len);
            fflush(file);
            read(fd1[0], &c, 1);
            if(strcmp(str, "exit")==0) 
            {
                waitpid(pid,0,0);
                break;
            }
        }
        close(fd[1]);
        close(fd1[0]);
    }

    fclose(file);
    return 0;
}