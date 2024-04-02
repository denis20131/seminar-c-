#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void sort(char* s)
{
    int i=0;
    while (s[i])
    {
        char min=s[i];
        int ind=i;
        int j=i+1;
        while (s[j])
        {
            if (s[j]<min)
            {
                min = s[j];
                ind=j;
            }
            j++;
        }
        char temp=s[i];
        s[i]=s[ind];
        s[ind] = temp;
        i++;
    }
}
int main(int argc,char *argv[]) // колво аргументов,массив строк
{
    int i;
    double ans=0;//сумма чисел
    int size=0;//для сложения строк размер
    char* end=0;
    for(i=1;i<argc;i++) //проходимся по всем строкам
    {
        double num=strtod(argv[i],&end); // end-первый символ после действительной части
        if (*end)
        {
            size+=strlen(argv[i]); //если символ!=0
        }
        else if (!(*end)){ans+=num;} // если равен нулю
    }
    printf("%lf\n",ans); //выводим сумму чисел
    int jmp=0;
    char* str = malloc(size); //выделяем память для конкатенации строк
    for(i=1;i<argc;i++)
    {
        strtod(argv[i],&end);
        if (*end)
        {
         strcat(str,argv[i]); //конкатенация строк
        }
    }
    printf("%s\n",str); //вывод обЪединения строк
    sort(str);
    printf("%s\n",str); //отсортированная строка
    free(str);// очищаем память
    return 0;
}