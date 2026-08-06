#include<stdio.h>
#include<stdlib.h>
#include"aluno.h"

Aluno * criar(int quantidade){
  Aluno * aluno = malloc(sizeof(Aluno) * quantidade);
  aluno->matricula = malloc(sizeof(char) * 50);
  return aluno;
}

void lerNotas(Aluno * a, int tamanho){
  for (int i = 0; i < tamanho; i++)
  {
    printf("Informe a nota %d: ", (i + 1));
    scanf(" %f", &a->notas[i]);
  }
}

void exibirNotas(Aluno * a, int tamanho){
  for (int i = 0; i < tamanho; i++)
  {
    printf("Nota %d: %.2f\n", (i + 1), a->notas[i]);    
  }
}

float calcularMedia(Aluno * a, int tamanho){
  float media;

  for (int i = 0; i < tamanho; i++)
  {    
    media += a->notas[i];
  }
  return media / tamanho;
}