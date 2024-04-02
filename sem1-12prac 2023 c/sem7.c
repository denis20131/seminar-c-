#include <stdio.h>
#include <sys/file.h>
#include <stdlib.h>
#include <string.h>

int func(const char* str){
    int len = strlen(str);
    int ans = 0;

    if(len !=9) {fprintf(stderr,"-1\n");exit(-1);}
    for(int i=0; i < len; i++){
        if(((str[i]=='x') && ((i)%3==2))||((str[i]=='w')&&((i)%3==1))||((str[i]=='r')&&((i)%3==0)))
        {
            ans<<=1;
            ans++;
        }
        else if(str[i]=='-'){
            ans <<=1;
        }
        else{
            fprintf(stderr,"-1\n");exit(-1);
        }
    }
    return ans;
}

char *func2(int val)
{
    if (val>0777) return NULL;
    char *str = malloc(10);

    for (int i = 0; i < 9; i++)
    {
        if ((val >> (8 - i)) & 1)
        {
            if ((8 - i) % 3 == 2)
                str[i] = 'r';
            if ((8 - i) % 3 == 1)
                str[i] = 'w';
            if ((8 - i) % 3 == 0)
                str[i] = 'x';
        }
        else
            str[i] = '-';
    }
    str[9] = '\0';

    return str;
}

int main(){

   //scanf ("%s",str);
    //printf("%o\n",a=func(str));
    //func2(a);
    char *t=NULL;
    t=func2(0777);
    if (t)
    printf("%s\n",t);
    else printf("NULL\n");
    return 0;
}