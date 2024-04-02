#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

void swap(int f, off_t aPos, off_t bPos)
{
    int numA, numB;

    lseek(f, aPos, SEEK_SET);
    read(f, &numA, sizeof(int));

    lseek(f, bPos, SEEK_SET);
    read(f, &numB, sizeof(int));

    lseek(f, aPos, SEEK_SET);
    write(f, &numB, sizeof(int));

    lseek(f, bPos, SEEK_SET);
    write(f, &numA, sizeof(int));
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Ошибка с параметрами");
        return 1;
    }

    int f = open(argv[1], O_RDWR);
    if (f == -1)
    {
        printf("Ошибка открытия файла");
        return 1;
    }
    int num;
    off_t neg_ind = 0, cur_ind = 0;
    while (read(f, &num, sizeof(signed int)))
    {
        if (num < 0)
        {
            swap(f, neg_ind * sizeof(signed int), cur_ind * sizeof(signed int));
            neg_ind++; //уведичиваем индекс отрицательных чисел
        }
        cur_ind++;
    }

    close(f);

    return 0;
}