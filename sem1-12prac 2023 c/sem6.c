#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	/* read(), write(), close() */
#include <fcntl.h>	/* open(), O_RDONLY */
#include <sys/stat.h>	/* S_IRUSR */
#include <sys/types.h>	/* mode_t */
typedef int STYPE;
typedef unsigned int UTYPE;
#define length sizeof(STYPE) * 8
void bin(char c[], UTYPE n)
{
    for (STYPE i = 0; i < length; i++)
        c[i] = '0';
    STYPE i = length - 1;
    while (n)
    {
        c[i] = (n % 2) + '0';
        n /= 2;
        i--;
    }
    c[length] = 0;
}

int main (int argc, char ** argv)
{
	int fd;
	char *s;
	if (argc < 3)
	{
		fprintf (stderr, "Too few arguments\n");
		exit (1);
	}
	int N=atoi(argv[2]);
	fd = open (argv[1],O_CREAT|O_RDWR|O_TRUNC,0666);
	if (fd < 0)
	{
		fprintf (stderr, "Cannot open file\n");
		exit (1);
	}	
	if ((fd)==-1) return -1;
	int k=rand()-rand();
	for (int i=0;i<N;i++)
		{
			printf("%d\n",k);
			write(fd,&k,4);
			k=rand()-rand();
		}
	close (fd);
	return 0;
}

