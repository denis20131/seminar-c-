#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("ошибка параметров");
        return 0;
    }

    int file = open(argv[1], O_RDONLY);
    FILE *newFile = fopen(argv[2], "r");
    if (newFile != NULL)
    {
        char a;
        printf("Изменить файл или нет?");
        scanf("%c", &a);
        if (a == 'n')
        {
            printf("Нет...");
            fclose(newFile);
            close(file);
            return 0;
        }
        fclose(newFile);
    }
    newFile = fopen(argv[2], "w");

    if (file == -1 || newFile == NULL)
    {
        printf("Ошибка с файлом");
        return 1;
    }

    signed int bInt;
    ssize_t bRead;
    while ((bRead = read(file, &bInt, sizeof(signed int))))
    {
        fprintf(newFile, "%d\n", bInt);
    }

    close(file);
    fclose(newFile);

    return 0;
}