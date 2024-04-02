#include <stdio.h>
#include <string.h>
#include <math.h>
#define length sizeof(STYPE) * 8
typedef int STYPE;
typedef unsigned int UTYPE;
void bin(char c[], UTYPE n)
{
    for (STYPE i = 0; i < length; i++)
        c[i] = '0';
    STYPE i = length - 1;
    while (n)
    {
        c[i] = (n % 2) + '0';
        n /= 2;
        i--;
    }
    c[length] = 0;
}

STYPE rev_bit(STYPE value)
{
    char str[length];
    bin(str, value);
    for (STYPE i = 0; i < length / 2; i++)
    {
        char buf = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = buf;
    }
    STYPE x = 0;
    for (STYPE i = 0; i < length; i++)
    {
        if (str[i] == '1')
            x += pow(2, length - 1 - i);
    }
    return x;
}
int main()
{
    STYPE n;
    scanf("%d", &n);
    printf("Данное число:%d\n", n);
    char s[length];
    bin(s, n);
    printf("Данное число в двоичном виде:%s\n", s);
    STYPE new = rev_bit(n);
    bin(s, new);
    printf("Число c противоположным порядком битов в двоичном виде:%s\n", s);
    return 0;
}