#include <stdio.h>

void bla(int n)
{
    if (n != 10000)
    {
        printf("Num: %d\n", n);
        bla(n + 1);
    }
}

int main()
{
    printf("Eu sou a main\n");
    bla(6);

    return 0;
}
