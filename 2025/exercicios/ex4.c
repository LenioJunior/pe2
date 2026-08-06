/*
Exerc ́ıcio 4: Atualiza ̧c ̃ao via Ponteiro

Implemente:
void atualizarMedia(Aluno *a, float novaMedia);
que atualiza a m ́edia de um aluno via ponteiro.
Conceitos: ponteiros e structs.
*/
#include<stdio.h>
#include<stdlib.h>
#include"aluno.h"

void atualizarMedia(Aluno *a, float novaMedia){
  a->media = novaMedia;
}

int exercicio4(){
  Aluno aluno;
  calcularMedia(&aluno, TAMANHO);
  printf("A media do aluno e: %.2f\n", aluno.media);
  exibirNotas(&aluno, TAMANHO);
  printf("Informe a nova média do aluno:\n");
  float newMedia;
  scanf("%f", &newMedia);
  atualizarMedia(&aluno, newMedia);
  printf("A nova media do aluno e: %.2f\n", aluno.media);
  return 0;
}

// int main(){
//   return exercicio4();
// }