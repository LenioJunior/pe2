#include <stdio.h>
#include <stdlib.h>

#define N 10

int * ordena(int * numeros, int tamanho){
    int cont1, cont2, aux;
    int * vetor = malloc(sizeof(int) * tamanho);

    for (int i = 0; i < tamanho; i++)
        vetor[i] = numeros[i];

    for (cont1 = 0; cont1 < tamanho; cont1++)
    {
        for (cont2 = cont1 + 1; cont2 < tamanho; cont2++)
        {
            aux = vetor[cont1];            
            if (vetor[cont2] < aux)
            {
                vetor[cont1] = vetor[cont2];
                vetor[cont2] = aux;
            }
        }
    }
    return vetor;
}

int questao4(){

    int numeros[] = {9, 6, 3, 2, 1, 7, 5, 4, 8, 0};

    int * ordenados = ordena(numeros, N);
    
    printf("--- Vetor Original ---\n");
    for (int cont1 = 0; cont1 < N; cont1++)
        printf("%d-", numeros[cont1]);

    printf("\n--- Vetor Ordenado ---\n");
    for (int cont1 = 0; cont1 < N; cont1++)
        printf("%d-", ordenados[cont1]);        

    printf("\n");
    return 0;
}