
#include<stdio.h>

int main(){

    int ** vetor;
    int t_linha0 = 3;
    int t_linha1 = 5;
    int t_linha2 = 2;

    vetor = malloc(3 * sizeof(int *));
    vetor[0] = malloc(t_linha0 * sizeof(int));
    vetor[1] = malloc(t_linha1 * sizeof(int));
    vetor[2] = malloc(t_linha2 * sizeof(int));
    
    vetor[0][0] = t_linha0;
    vetor[1][0] = t_linha1;
    vetor[2][0] = t_linha2;

    int contador = 1;
    for (int linha = 0; linha < 3; linha++)
    {   
        int sizeLinha = vetor[linha][0];
        printf("Size Colunas: %d\n", sizeLinha);
        for (int coluna = 1; coluna < sizeLinha; coluna++)
        {
            vetor[linha][coluna] = contador++;
        }        
    }

    for (int linha = 0; linha < 3; linha++)
    {   
        int sizeLinha = vetor[linha][0];
         printf("Elementos da Linha: %d (%d itens)\n", linha, sizeLinha);
        for (int coluna = 1; coluna < sizeLinha; coluna++)
        {
            printf("Item %d: %d\n", coluna, vetor[linha][coluna]);
        }        
    }    

    return 0;
}