#include <stdio.h>

int main()
{
    int n1 = 20;
    int n2 = 10;

    if (n2 > n1)
        n1 = 100;
    else
        n2 = 200;

    printf("n1: %d\n", n1);
    printf("n2: %d\n", n2);

    return 0;
}
