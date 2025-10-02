#include<stdio.h>
#include<stdlib.h>


void ordenar(int * vetor, int tamanho){
  int temp;

  for (int i = 0; i < tamanho - 1; i++)
  {
    for (int j = i+1; j < tamanho; j++)
    {
      if(vetor[i] > vetor[j]){
        temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
      }
    }    
  }  
}

void exibir(int * vetor, int tamanho){
  printf("Valores do vetor:\n");
  for (int i = 0; i < tamanho; i++){
    if(i == tamanho - 1){
      printf("%d\n", vetor[i]);
    } else {
      printf("%d -", vetor[i]);
    }
  }
}

// Dado um vetor de qualquer tamanho, encontrar o maior e o menor elemento,
// armazenando em ponteiros.
int main(){
  int vetor [] = {67, 23, 18, 4, 33, 26, 55, 98, 1, 6};
  int * menor = &vetor;
  int * maior = &vetor;

  exibir(vetor, 10);

  for (int i = 0; i < 10; i++)
  {
    // if(vetor[i] > * maior){
    //   maior = &vetor[i];
    // }
    maior = vetor[i] > * maior ? &vetor[i] : maior;

    // if(vetor[i] < * menor){
    //   menor = &vetor[i];
    // }
    menor = vetor[i] < * menor ? &vetor[i] : menor;
  }
  
  printf("O menor valor eh: %d\n", * menor); // 1
  printf("O maior valor eh: %d\n", * maior); // 98

  ordenar(vetor, 10);
  exibir(vetor, 10);
}