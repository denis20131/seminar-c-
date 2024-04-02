#include<stdio.h>
#include <string.h>
#include <math.h>
#define length 32

void bin(char c[],unsigned int n)
{
    for (int i=0;i<length;i++) 
        c[i]='0';
    int i=length-1;
    while (n)
    {
        c[i] = (n%2) + '0';
        n/=2;
        i--;
    }
    c[length]=0;
}

unsigned int func(unsigned int x)
{
    char s[length];
    unsigned int m = x & 0x00FFFF00;
    unsigned int x1= x & 0x000000FF;
    unsigned int x4= (x & 0xFF000000) >> 24;
    if (x1==x4)
        {
          m= x & 0xFF0000FF;   
        }
    else
        {
          x1 = x1 << 24;
          m = m | x1 | x4 ;
        }
    return m; 
}

int main()
{unsigned int n;
    scanf("%u",&n);
    printf("Данное число:%u\n",n);
    char s[length];
    bin(s,n);
    printf("Данное число в двоичном виде:%s\n",s);
    unsigned int new = func(n);
    bin(s,new);
    printf("Новое число в двоичном виде:%s\n",s);
    return 0;
}