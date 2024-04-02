#define __USE_XOPEN_EXTENDED
// #define __USE_MISC
#include <stdio.h>
#include <sys/file.h>
#include <dirent.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
// #include <fcntl.h>

void print_sym_link(DIR*);
void print_directory(char *);
int main()
{
    DIR* d =opendir(".");
    print_sym_link(d);
    print_directory(".");
    return 0;
}
void print_sym_link(DIR* d)
{
    char buf[256];
    int n;
    struct dirent* file;
    while(file = readdir(d))
    {
        if (file -> d_type == DT_LNK)
            {

            }
    }
}
