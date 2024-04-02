#include<stdio.h>
#include<stdlib.h>
#define b 8
#define length 10
void printb(int n)
{
    char ans[b];
    for (int i = b-1; i >= 0; i--)
    {
        ans[i] = (n & 0x01) ? '1' : '0';
        n=n >> 1;
    }
    printf("%s\n",ans);
}

int func(char *a,int N,int n)
{
  int y=n%8;
  int x=n/8;
  return((a[x] >> (7-y)) & 1);
}

int enumer(char* s,int n)
{
    int count=0;
    int symbs=0;
    int max=0;
    for (int i=0;i<length*8;i++)
    {
        if (func(s,length,i)==1) symbs++;
        else
        {
            if (symbs>=n) count++;
            if (symbs>max) max=symbs;
            symbs = 0;
        }
    }
    printf("Max: %d\n",max);
    return count;
}

int main()
{   
    int n;
    char t;
    char a[length];
    scanf("%d", &n);
    getchar();
    for (int i=0;i<length-1;i++)
    {
     a[i]=getchar();
    }
    for (int i=0;i<length-1;i++)
    {
     printf("%d:  ",i);
     printb(a[i]);
    }   
    printf("Ans: %d\n",enumer(a,n));
}