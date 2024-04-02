#include<stdio.h>
#define b 8
int printb(int n)
{
    char ans[b];
    for (int i = b-1; i >= 0; i--)
    {
        ans[i] = (n & 0x01) ? '1' : '0';
        n=n >> 1;
    }
    printf("%s\n",ans);
}

void func(char *a,int N,int n)
{
  int x=n/8;
  int y=n%8;
  printf("%d\n",(a[x] >> y) &1); // a справа налево
  printf("%d\n",(a[x] >> (7-y)) & 1); // b  слева направо
}
int main(int argc, char** argv){
    char a[10]={'1','2','3','4','5','6','7','8','9'};
    int n; int m;int N=10;
    scanf("%d", &n);
    for (int i=0;i<10;i++)
    {
     printf("%d:  ",i);
     printb(a[i]);
    }   
    func(a,N,n);
    return 0;
}