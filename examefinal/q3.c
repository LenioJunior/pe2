#include <stdio.h>
#include <stdlib.h>

void realizar_operacao(int *a, int *b) {
    if (*a <= 10) {
        *a += *a;
    } 
    else {
        *a -= *a;
    }
    if (*b > 10) {
        *b += *b;
    } 
    else {
        *b -= *b;
    }
    *a = *a + *b;
}


int questao3(){
    int x = 5;
    int y = 11;
    int *ptr_x = &x;
    int *ptr_y = &y;    

    realizar_operacao(ptr_x, ptr_y);

    printf("O valor de x é: %d\n", x);
    printf("O valor de y é: %d\n", y);

    return 0;
}