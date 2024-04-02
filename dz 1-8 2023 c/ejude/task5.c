#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <math.h>
#include <stdlib.h>

long long numb=0;

void f1(int sig)
    {
        signal(SIGTERM,f1);
        exit(0);
    }

void f2(int sig)
    {
        signal(SIGINT,f2);
        static int count=0;
        count++;
        if (count==4) exit(0);
        printf("%lld\n",numb);
        fflush(stdout);
    }

int main()
    {
        printf("%d\n",getpid());
        fflush(stdout);
        long long low,high;
        scanf("%lld",&low);
        scanf("%lld",&high);
        signal(SIGTERM,f1);
        signal(SIGINT,f2);
        for (long long i=low;i<high;i++)
        {
            int b=1;
            if (!(i%2)) continue;
            for (long long j=2;j<=sqrtl(i);j++)
            {
                if (!(i%j))
                    {b=0;break;}
            }
            if (b==1) numb=i;
        }
        printf("%d\n",-1);
        fflush(stdout);
        return 0;
    }