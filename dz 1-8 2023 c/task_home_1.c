#include <stdio.h>
#include <stdlib.h>
#define block 4

char* read()
{
    char* string = (char*)malloc(block);
    char c;
    int count = 0;
    int len=block;
    int* check;
    while(((c=getchar())!=EOF)&&(c!='\n'))
    {
        string[count++] = c;
        if(count==len)
        {
            check = (int*)malloc(block);
            if (check==NULL)
            {
                free(check);
                free(string);
                fprintf(stderr,"переполнение памяти\n");
                exit(1);
            }
            free(check);
            string = (char*) realloc(string,len+=block);
        }
    }
    string[count]=0;
    string = (char*)realloc(string,(count+1));
    return string;
}

int main()
{
    char* string = read();
    printf("%s\n",string);
    free(string);
    return 0;
}
