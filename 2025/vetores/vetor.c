#include<stdio.h>
#include<stdlib.h>

int * alocaVetor(int tamanho){
  return malloc(tamanho * sizeof(int));
}

void preenche (int * vetor, int tamanho){
  for(int i=0; i<tamanho;i++){
    printf("Informe um valor\n");
    scanf("%d", vetor++);
  }
}

void imprime (int * vetor, int tamanho){
  for (int i = 0; i < tamanho; i++)
  {
    printf("%d\n", * vetor++);
  }
  
}