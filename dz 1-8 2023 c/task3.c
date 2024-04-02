#include <stdio.h>
#include <stdlib.h>
#include <string.h>
double rev_d(double x)
{
    char s[100];
    sprintf(s,"%f",x);
    int sign;
    if (x>0) sign=1;
    else sign=-1;
    char t;
    int length=strlen(s);
    for (int i=0,j=strlen(s)-1;i<j;i++,j--) 
    {
        t=s[i];
        s[i]=s[j];
        s[j]=t;
    }
    return strtod(s,0)*sign;
}
double rev1_d(double x) 
{
    char *s = (char*)calloc(sizeof(char),308);
    sprintf(s,"%f",x);
    int sign;
    if (x>0) sign=1;
    else sign=0;
    char *s_new = (char*)calloc(sizeof(char),308);
    if (!sign) s_new[0] = '-';
    else s_new[0]='+';
    int length=strlen(s);
    int i=1;
    for (i=1;i<length;i++)
    {
        s_new[i] = s[length-i];

    }
    if (x>0) s_new[i]=s[0];     
    return strtod(s_new,0);
}

int main()
{   double x;
    scanf("%lf",&x);
    printf("%g\n",rev_d(x));
    return 0;
}