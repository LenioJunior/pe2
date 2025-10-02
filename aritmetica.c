#include<stdio.h>
#include<stdlib.h>
#define SIZE 5

int main(){
    /* Criar um vetor de 5 posições e efetuar a leitura de valores
    utilizando apenas aritmética de ponteiros*/
  int vetor[SIZE];  

  for (int * pvetor = vetor; pvetor < (vetor + SIZE); pvetor++){
    printf("Informe o valor:\n");
    scanf("%d", pvetor);
    printf("Valor: %d\n", *(pvetor));
  }
}