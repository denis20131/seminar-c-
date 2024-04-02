#include <stdio.h>
#include <sys/file.h>
#include <dirent.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

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

char* get_type(struct dirent* d){
    switch(d->d_type)
    {
        case DT_LNK: return "LNK";
        case DT_DIR: return "DIR";
        case DT_REG: return "REG";
    }
    return "other";
}

void print_dir()
    {
    DIR* dir = opendir(".");
    struct dirent* file;
    char* a_type, *a_name, *a_p;
    char filename[1024];
    struct stat st;
    int d;
    while(file= readdir(dir))
        {
            sprintf(filename, "./%s", file->d_name);
            stat(filename, &st);
            a_p = func2(st.st_mode & (S_IRWXU|S_IRWXG|S_IRWXO));
            a_name = file->d_name;
            d = st.st_ino;
            a_type = get_type(file);
            printf("p: %s, fd: %d, Type: %s, Name: %s\n", a_p , d, a_type,a_name);
            free(a_p);
        }
    closedir(dir);
    }

int main()
{
    print_dir();
    return 0;
}

