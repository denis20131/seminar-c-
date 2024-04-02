#include <stdio.h>

int main(int argc, char* argv[])
{
 if (argc!=3) return 1;
 FILE* memory_phys;
 if ((memory_phys = fopen(argv[1], "r"))==NULL) return 1;
 unsigned short base, num, virtualadres,phys_adres,offset,elem;
 sscanf(argv[2],"%hx",&base);
 while (scanf("%hx",&virtualadres) != EOF)
 {
    num = virtualadres >> 9;
    offset = virtualadres & 0x1ff;
    fseek(memory_phys, base+(num*2), SEEK_SET);
    fread(&phys_adres,sizeof(short),1,memory_phys);
    phys_adres += offset;
    fseek(memory_phys, phys_adres, SEEK_SET);
    fread(&elem,sizeof(short),1,memory_phys);
    printf("%hu\n",elem);
 }
 fclose(memory_phys);
 return 0;
}
