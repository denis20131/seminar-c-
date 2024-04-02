#include <stdio.h>
#define b 32

void printb(int n)
{
    char ans[b];
    for (int i = b-1; i >= 0; i--)
    {
        ans[i] = (n & 0x01) ? '1' : '0';
        n=n >> 1;
    }
    printf("%s\n", ans);
}
int main(int argc, char** argv){
    int n;
    scanf("%d", &n);
    printb(n);
    printf("\n");
    return 0;
}