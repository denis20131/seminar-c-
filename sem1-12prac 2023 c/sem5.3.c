#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int strings_in_file(FILE *stream)
{
    int ans = 1;
    int pos=0;
    int c;
    while ((c=fgetc(stream))!=EOF)
    {
        if (c=='\n') ans++;
        pos++;
    }
    fseek(stream,-1,SEEK_END);
    c = fgetc(stream);
    if (c==EOF) ans-=1;
    if (c!='\n')
    {
        fseek(stream,0,SEEK_END);
        fputc('\n',stream);
    }
    fseek(stream, 0, SEEK_SET);
    return ans;
}

/*массив с номерами байтов*/int* mas_number(FILE* file){
    char a;
    int i = 0;
    int size=strings_in_file(file);
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
    fseek(file, 0, SEEK_SET);
    return mas;
    free(mas);
}

/*нужная строка по номеру void get_str(FILE* file, int str, int* mas, int count){
    if((str < 0)||(str >= count)){
        printf("ERROR");
        return;
    }
    fseek(file, mas[str], SEEK_SET);
}*/

void write_del_empty(int *mas,FILE *file,FILE *new_file)
{
    char a;
    new_file=fopen("new.txt","w");
    fseek(file, 0, SEEK_SET);
    int count = strings_in_file(file); //строки
    int m=0;
    for(int i=0; i < count-1; i++)
    {
        fseek(file, mas[i], SEEK_SET);
      // printf("%d %d\n",mas[i],mas[i+1]);
        if (mas[i+1]-mas[i]==1)
        {
         m++;
         if (m>=2) continue;
        }
        else m=0;
        while ((a=fgetc(file))!='\n') fputc(a,new_file);
        fputc('\n',new_file);
    }
    fclose(new_file);
}

    void more(int c_string,int *mas,FILE *file,int s,int num,int linenum)
{
    char a;
    FILE *file_new;
    if (s==0) write_del_empty(mas,file,file_new);
        file_new=fopen("t.txt","r");
        int *m=mas_number(file_new); //массив длин строк в файле
        int count=strings_in_file(file_new); // количество строк в новом файле
        if (count<10) num=count;
        for(int i=linenum; i < num-1; i++)
    {
        fseek(file_new, m[i], SEEK_SET);
        while ((a=fgetc(file_new))!='\n') putchar(a);
        putchar(10);
    }
    free(m);
    fclose(file_new);
    
}
int main(int argc,char **argv)
{
    char c;
    if ((argc<2) || (argc>5)) 
    {
        perror("Ошибка аргументов\n");
        exit(1);
    }
    FILE *stream;
    int s=0;
    int num=10;
    int linenum=0;  
    /*switch (argc)
     {
        case 2:
              if (!(stream = fopen(argv[1],"r+")))
                {
                        fprintf(stderr,"Ошибка при открытии файла\n");
                        exit(1);
                }
            break;
        case 3:
             if (!(stream = fopen(argv[2],"r+")))
                {
                        fprintf(stderr,"Ошибка при открытии файла\n");
                        exit(1);
                }
            if (!(strcmp((argv[1]),"-s")))
                s=0;
            else
                if (atoi(argv[1])<0)
                    num=(atoi(argv[1])*(-1));
                else
                    linenum=atoi(argv[1]);
            break;
        case 4:
             if (!(stream = fopen(argv[3],"r+")))
                {
                        fprintf(stderr,"Ошибка при открытии файла\n");
                        exit(1);
                }
            if (!(strcmp((argv[1]),"-s")))
                s=1;
            else
                if (atoi(argv[1])<0)
                    num=(atoi(argv[1])*(-1));
                else
                    linenum=atoi(argv[1]);
            if (!(strcmp((argv[2]),"-s")))
                s=1;
            else
                if (atoi(argv[2])<0)
                    num=(atoi(argv[2])*(-1));
                else
                    linenum=atoi(argv[1]);
            break;
        case 5:
             if (!(stream = fopen(argv[4],"r+")))
                {
                        fprintf(stderr,"Ошибка при открытии файла\n");
                        exit(1);
                }
            s=1;
            num=atoi(argv[1])*(-1);
            linenum=atoi(argv[2]);
            break;
     }*/
     stream = fopen(argv[1],"r+");
    int* mas = mas_number(stream); //массив с номерами байтов       
    int c_string=strings_in_file(stream);
    FILE *file_new=fopen("t.txt","r");
    int *m=mas_number(file_new); //массив длин строк в файле
    scanf("%c",&c);
    while(c!='q') 
    {
        more(c_string,mas,stream,s,10,linenum);
        scanf("%c",&c);
    }
    fclose(stream);
    fcloze(file_new);
    free(m);
    return 0;
}