#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc!=4)
            {
                printf("error args\n");
                exit(1);
            }

    int f1=open(argv[1],O_RDONLY,0664);
    if (f1==-1) {printf("error f1\n");exit(1);}

    int f2=open(argv[2],O_RDONLY,0664);
    if (f2==-1) {printf("error f2\n");exit(1);}

    int f3=open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,0664);
    if (f3==-1) {printf("error f3\n");exit(1);}

    char c1,c2;
    if (!(read(f1,&c1,1) && read(f2,&c2,1)))
    {
        printf("Есть пустой файл\n");
        close(f1);
        close(f2);
        close(f3);
        exit(0);
    }

    lseek(f1,0,SEEK_SET);
    lseek(f2,0,SEEK_SET);
    pid_t pid1,pid2;

    int s1_s2[2],s2_s1[2],f_s[2];

    if ((pipe(s1_s2)==-1) || (pipe(s2_s1)==-1) || (pipe(f_s)==-1) )
        {
            printf("error pipe\n");
            exit(1);
        }

    if ((pid1=fork())<0)
            {
                printf("error fork1\n");
                exit(2);
            }

    if (pid1==0)
        {
            close(s1_s2[0]);
            
            close(s2_s1[1]);
            
            close(f_s[0]);
            
            close(f2);

            while (1)
            {
                int count_chars=0;
                int k;
                char c;
                while ((k=read(f1,&c,1))&&(c!='\n'))
                {
                    write(f3,&c,1);
                    count_chars++;
                }
                if ((count_chars+k)==0)
                {
                    int fl=0;
                    write(s1_s2[1],&fl,4);
                    read(s2_s1[0],&fl,4);
                    write(f_s[1],&fl,4);
                    fl = 2;
                    write(f_s[1],&fl,4);
                    
                    close(s1_s2[1]);
                    close(s2_s1[0]);
                    close(f_s[1]);
                    close(f1);
                    close(f3);
                    exit(0);
                }
                c = '\n';
                write(f3,&c,1);
                int fl = 1;
                write(s1_s2[1],&fl,4);
                read(s2_s1[0],&fl,4);
                if (!fl)
                {
                    int count_chars=0,count=0;
                    while (read(f1,&c,1))
                    {
                        if (c=='\n') 
                            count++;
                        count_chars++;
                    }
                    if (count_chars) count++;
                    write(f_s[1],&count,4);
                    fl = 1;
                    write(f_s[1],&fl,4);
                    close(s1_s2[1]);
                    close(s2_s1[0]);
                    close(f1);
                    close(f3);
                    exit(0);
                }
            }
    }
    
    if ((pid2=fork())<0)
            {
                printf("error fork2\n");
                exit(2);
            }

    if (pid2==0)
        {
            close(f1);

            close(f_s[1]);
            close(f_s[0]);

            close(s2_s1[0]);

            close(s1_s2[1]);

            while(1)
            {
                int fl;
                read(s1_s2[0],&fl,4);

                if (fl==0)
                {
                    char c;
                    int count=0;
                    int count_chars=0;

                    while (read(f2,&c,1))
                    {
                        if (c=='\n') 
                            count++;
                        count_chars++;
                    }

                    if (count_chars) count++;

                    write(s2_s1[1],&count,4);

                    close(f2);
                    close(f3);

                    close(s2_s1[1]);
                    close(s1_s2[0]);

                    exit(0);   
                }

                char c;
                int k;
                
                while ((k=read(f2,&c,1))&&(c!='\n'))
                    write(f3,&c,1);

                if (k==0)
                {
                    fl = 0;
                    write(s2_s1[1],&fl,4);
                    close(f2);
                    close(f3);
                    close(s2_s1[1]);
                    close(s1_s2[0]);
                    exit(0);
                }
                c = '\n';
                write(f3,&c,1);
                fl = 1;
                write(s2_s1[1],&fl,4);
            }
        }

    {
        close(f1);
        close(f2);
        close(f3);
        
        close(s1_s2[0]);
        close(s1_s2[1]);

        close(s2_s1[0]);
        close(s2_s1[1]);

        close(f_s[1]);

        int count_str,num_file;
        read(f_s[0],&count_str,4);
        read(f_s[0],&num_file,4);
        if (count_str==0)
            exit(0);
        printf("Необработанных строк из файла %d: %d\n",num_file,count_str);int id;
        wait(0);
        wait(0);
        printf("%d %d %d\n", pid1, waitpid(pid1,&id,0), id);
        printf("%d %d %d\n", pid2, wait(&id), id);
    }
}