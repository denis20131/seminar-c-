#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int count_strings(char *name)
{
    FILE *f;
    if (!(f = fopen(name,"r+")))
    {
        fprintf(stderr,"Ошибка при открытии файла\n");
        exit(1);
    }

    int ans = 1;
    int pos=0;
    int c;
    while ((c=fgetc(f))!=EOF)
    {
        if (c=='\n') ans++;
        pos++;
    }
    fseek(f,-1,SEEK_END);
    c = fgetc(f);
    if (c==EOF) ans-=1;
    if (c!='\n')
    {
        fseek(f,-1,SEEK_END);
        fputc('\n',f);
    }
    fclose(f);
    return ans;
}

int *info_strings(char *s)
{
    int *ans=NULL;
    int strings = 0;
    FILE *f;
    f=fopen(s,"r");
    int len=0;
    int c;
    while ((c=fgetc(f))!=EOF) //храним номер символа в файле с которого начинается строка
    {
        if (c!='\n') len++; //храним длину файла
        else
        {
            strings++;
            ans = (int*)realloc(ans,4*strings);
            ans[strings] = len;
            len = 0;
        }
    }
    fclose(f);
    return ans;
}

void print_str(char *s,int number)
{
    int str_count = count_strings(s); // количество строк
    int *strings = info_strings(s);
 /*ошибка*/ if (number>=str_count)
    {
        fprintf(stderr,"Нет такой строки в файле\n");
        exit(1);
    }
    FILE *f;
   /*ошибка*/   if (!(f=fopen(s,"r")))
    {
        fprintf(stderr,"Ошибка при открытии файла\n");
        exit(1);
    }
    for (int i=0;i<number;i++)
    {
        fseek(f,strings[i]+1,SEEK_CUR);     // смещаемся пока не дойдём до нужной позиции в файле   
    }
    int c;
    while (((c=fgetc(f))!='\n')&&(c!=EOF)) putchar(c); //выводим строку
    putchar('\n');
    free(strings);
}

int main(int argc,char **argv)
{
    int c;
    if (argc<2) 
    {
        perror("Не переданы аргументы\n");
        exit(1);
    }
    printf("Введите число\n");
    scanf("%d",&c);
    printf("Строка: ");
    print_str(argv[1],c);
    return 0;
}
/*void conect_empty_string(FILE *f)
{
    char c;
    int *strings=info_strings("t.txt");
    int number=count_strings("t.txt");
    while (((c=fgetc(f))!='\n')&&(c!=EOF)) putchar(c); 
    free(strings);

}*/

/*void more(char *s, char *num,char *linenum);
if (s) {

        }*/
