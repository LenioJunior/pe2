#include <stdio.h>
#include <stdlib.h>

void ajusta(int *p, int tamanho) {
    int *fim = p + tamanho;

    while (p < fim) {
        if (*p % 2 == 0) {
            *p += 1;
        } else {
            *p += 5;
        }
        p++;
    }
}


int questao2(){
    int tamanho = 5;

    int x[] = { 5, 4, 2, 9, 22 };

    ajusta(x, tamanho);

    for (int i = 0; i < tamanho; i++)
        printf("%d ", x[i]);
    
    printf("\n");

    return 0;
}