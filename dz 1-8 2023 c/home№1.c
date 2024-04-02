#include <stdio.h>
#include <stdlib.h>
#define block 4

char* read()
{
    char* str = (char*)calloc(sizeof(char),block);
    char c;
    int del = block;
    int count = 0;
    int size=0;
    int *check;
    while((c!='\n') && ((c=getchar())!=EOF))
    {
        if(del == 0)
            {
                
                del = block;
                size=count+del;
                str = (char*) realloc(str,size);
                str[count] = c;
                count+=1;
                del-=1;
            }
        else 
            if(del > 0)
                {
                    str[count] = c;
                    count+=1;
                    del-=1;
                }
    }
    str = (char*)realloc(str,(count+1));
    return str;
}

int main()
{
    char* str = read();
    printf("%s",str);
    free(str);
    return 0;
}

