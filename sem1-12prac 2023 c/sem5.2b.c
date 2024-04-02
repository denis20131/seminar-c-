#include <stdio.h>
#include <stdlib.h>

/*подсчёт строк*/ int fstrcounte(FILE* file)
{
    char a;
    int counter = 0;
    while((a = fgetc(file))!=EOF){
        counter += (a == '\n');
    }

    fseek(file, -1, SEEK_CUR);
    if ((a = fgetc(file)) != '\n')
    {
        fseek(file, -1, SEEK_CUR);
        fputc('\n', file);
        counter++;
    }
    fseek(file, 0, SEEK_SET);
    return counter;
}

/*массив с номерами байтов*/int* mas_number(FILE* file, int size){
    char a;
    int i = 0;
    int counter = 0;
    int *mas = malloc((size+1)*sizeof(int));
    mas[0] = 0;
    while((a = fgetc(file))!=EOF)
    {
        counter++;
        if(a == '\n'){
            i++;
            mas[i] = counter;
        }
    }
    return mas;
}

/*нужная строка по номеру*/void get_str(FILE* file, int str, int* mas, int count){
    if((str < 0)||(str >= count)){
        printf("ERROR");
        return;
    }
    fseek(file, mas[str], SEEK_SET);
    char a;
}

void new_file(FILE* file, int*mas, int s)
{
    FILE* newf = fopen("new", "w");
     if(!newf){
        exit(-1);
    }
    int* delta = malloc(sizeof(int)*s);
    for(int i = 0; i < s; i++){
        delta[i] = mas[i+1] - mas[i]; //хранит длину строки
    }
    putchar('\n');
    int tmp;
    int noSwap;
    for(int i = s-1; i >= 0; i--){
        noSwap = 1;
        for(int j = 0; j < i; j++)
        {
            if(delta[j] > delta[j+1]){
                tmp = delta[j];
                delta[j] = delta[j+1];
                delta[j+1] = tmp;
                tmp = mas[j];
                mas[j] = mas[j+1];
                mas[j+1] = tmp;
                noSwap = 0;
            }
        }
        if(noSwap==1) break;
    }
    char a;
    for(int i=0; i < s; i++){
        fseek(file, mas[i], SEEK_SET);
        while((a=fgetc(file))!='\n'){
            fputc(a, newf);
        }
        fputc('\n', newf);
    }
    free(delta);
    fclose(newf);
}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("ERROR1");
        exit(-1);
    }
    FILE* f1 = fopen(argv[1], "r+");
    if(!f1){
        exit(-1);
    }
    int count = fstrcounte(f1); //строки
    int* mas = mas_number(f1, count); //массив с номерами байтов
    int str;
    new_file(f1, mas, count);
    free(mas);
    fclose(f1);
    return 0;
}