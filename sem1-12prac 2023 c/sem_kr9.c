#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define len 100
int main(int argc,char **argv)
{
    if (argc!=2) 
        {
            printf("error parametr");
            exit(1);
        }
    int pid1;
    int fd[2];
    int fd1[2];
    pipe(fd);
    pipe(fd1);
    if (fd == -1 || fd1 == -1)
    {
        perror("Failed to open pipes");
        exit(1);
    }
    int f= open(argv[1],O_WRONLY,O_CREAT,O_TRUNC,0666);
    if (f==-1)
        {printf("error open file");
            exit(1);}
    if ((pid1=fork())==0)
        {
            char c;
            char s[len];
            close(fd[1]);
            close(fd1[0]);
           while(1)
           {
            if ((read(fd[0],&c,1)) || (read(fd[0],s,len)<=0)) break;
            int i=0;int count=0;
            while(i<sizeof(s))
             {if (s[i]==c) count++;
                i++;}
            dprintf(f," %d\n",count);
            write(fd1[1],&count,4);
           }
            close(fd[0]);
            close(fd1[1]);
            exit(0);
        }
    else
        if (pid1<0)
        {
            printf("fork pid1");
                exit(1);}
    else
        {
            close(fd[0]);
            close(fd1[1]);
            char c;
            char s[len];
            scanf("%s",s);
            scanf("%c",&c);
            while ((scanf("%c",&c)==1) && (scanf("%s",&s)==1) && ((strcmp(s,"exit")!=0)!=0))
                {
                    dprintf(f,"%s",s);
                    write(fd[1],&c,1);
                    write(fd[1],&s,sizeof(s));
                    read(fd1[0],NULL,4);
                    fflush(stdin);
                }
        }
    close(fd[1]);
    close(fd1[0]);
    close(f);
}