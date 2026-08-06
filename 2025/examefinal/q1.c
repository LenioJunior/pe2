#include <stdio.h>
#include <stdlib.h>

int ** alocaMatriz(int linhas, int colunas);
void preenche (int **matriz, int linhas, int colunas);
void imprime (int **matriz, int linhas, int colunas);
int * criaVetor(int colunas);
void liberarMatriz (int **matriz, int linhas);

int ** alocaMatriz(int linhas, int colunas){
    int ** matriz = malloc(sizeof(int) * linhas);

    for (int i = 0; i < linhas; i++)
        matriz[i] = criaVetor(colunas);

    return matriz;    
}

void preenche (int **matriz, int linhas, int colunas){
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            matriz[i][j] = (i * colunas) + j +1;
}

void imprime (int **matriz, int linhas, int colunas){
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++)
            printf("%.3d ", matriz[i][j]);
        printf("\n");
    }
}

int * criaVetor(int colunas){
    return malloc(sizeof(int) * colunas);
}

void liberarMatriz (int **matriz, int linhas){
    for (int i = 0; i < linhas; i++)
        free(matriz[i]);
    
    free(matriz);
}

int questao1(){
    int linhas = 3;
    int colunas = 4;

    printf("\n");
    int ** matriz = alocaMatriz(linhas, colunas);
    preenche(matriz, linhas, colunas);
    imprime(matriz, linhas, colunas);
    liberarMatriz(matriz, linhas);

    return 0;
}