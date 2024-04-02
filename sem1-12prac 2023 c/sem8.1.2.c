#include <stdio.h>
#include <sys/file.h>
#include <dirent.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char **argv)
{
    if (argc!=2){printf("ERROR\n");exit(1);}
    int N=atoi(argv[1]);
    for (int i=0;i<N;i++) printf("\nPID=%d\n",getpid());
    exit(1);
}