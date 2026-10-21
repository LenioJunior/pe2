#include <stdio.h>
int main()
{
    int x = 1, soma = 0;
    while (x <= 10)
    {
        if (x % 3 == 0)
            soma += x;
        else if (x % 2 == 0)
            soma -= x;
        x++;
    }
    printf("soma = %d\n", soma);
    return 0;
}