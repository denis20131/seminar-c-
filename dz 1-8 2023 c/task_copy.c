#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int strings_in_file(FILE *stream)
{
    int ans = 1;
    int c;
    while ((c=fgetc(stream))!=EOF)
        if (c=='\n') ans++;

    fseek(stream,-1,SEEK_END);
    c = fgetc(stream);

    fseek(stream, 0, SEEK_SET);
    return ans;
}

/*массив с номерами байтов*/int* mas_number(FILE* file){
    char a;
    int i = 0;
    int size=strings_in_file(file);
    int counter = 0;
    int *mas = malloc((size)*sizeof(int));
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
}

    void more(int c_string,int *mas,FILE *file,int num,int *linenum)
{
    char a;
    int m=0;
    int k=0;
    int i=*linenum;
    int p=i;
    while(k<num)
    {
        if (i>=c_string) {*linenum=-1;return;}
        fseek(file, mas[i], SEEK_SET);
        if ((i+1)!=c_string)
            {if ((mas[i+1]-mas[i]==1))
            {
            m++;
            if (m>=2) {i++;continue;}
            }
            else m=0;
            }
        if ((i+1)!=c_string)
            {while ((a=fgetc(file))!='\n' && (a!=EOF)) 
                putchar(a);
                    putchar(10);}
        else
            if ((a=fgetc(file))!=EOF)
                {
                    while ((a!='\n') && (a!=EOF)) 
                    {putchar(a);
                    a=fgetc(file);}
                    putchar(10);
                }
        k++;
        i++;
        if ((a==EOF) || (i>=c_string)) {*linenum=-1;return;}
    }
    *linenum+=(i-p);
    return;
}

  void more2(int c_string,int *mas,FILE *file,int num,int *linenum)
{
    char a;
    int k=0;
    int i=*linenum;
    int p=i;
    while(k<num)
    {
        fseek(file, mas[i], SEEK_SET);
        while ((a=fgetc(file))!='\n' && (a!=EOF)) putchar(a);
        putchar(10);
        i++;
        k++;
        if ((a==EOF) || (i>=c_string)) {*linenum=-1;return;}
    }
    *linenum+=(i-p);
    return;
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
    switch (argc)
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
                {
                s=1;
                }
            else
                if (atoi(argv[1])<0)
                    num=(atoi(argv[1])*(-1));
                else
                    linenum=atoi(argv[1])-1;
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
                    linenum=atoi(argv[1])-1;
            if (!(strcmp((argv[2]),"-s")))
                s=1;
            else
                if (atoi(argv[2])<0)
                    num=(atoi(argv[2])*(-1));
                else
                    linenum=atoi(argv[2])-1;
            break;
        case 5:
             if (!(stream = fopen(argv[4],"r+")))
                {
                        fprintf(stderr,"Ошибка при открытии файла\n");
                        exit(1);
                }
            s=1;
            num=atoi(argv[2])*(-1);
            linenum=atoi(argv[3])-1;
            break;
     }
    //printf("%d  %d  %d %d\n",s,num,linenum,strings_in_file(stream));
    int c_string=strings_in_file(stream); //кол-во строк в файле
   if (linenum>=c_string) 
                {
                        fclose(stream);
                        fprintf(stderr,"Ошибка с параметрами\n");
                        exit(1);
                }
   int* mas = mas_number(stream); //массив с номерами байтов                 
    if (s==1)
        {
            while(1) 
                {
                    scanf("%c",&c);
                    if (c=='-') //выводится по нажатию клавиши "-"
                            more(c_string,mas,stream,num,&linenum); 
                    if ((c=='q') || (linenum==-1)) //прекращаются вывод по нажатию клавиши "q" и когда заканчивается файл
                            break;
                }
        }
    else
            while(1) 
                {
                    scanf("%c",&c);
                    if (c=='-')
                            more2(c_string,mas,stream,num,&linenum); 
                    if ((c=='q') || (linenum==-1))
                        break;
                    c=getchar();
                }

    fclose(stream);
    free(mas);
    return 0;
}