/*
Exerc ́ıcio 2: Fun ̧c ̃ao para C ́alculo de M ́edia

Usando a struct do exerc ́ıcio anterior, escreva uma fun ̧c ̃ao:
float calcularMedia(Aluno a);
que retorne a m ́edia do aluno a partir de um vetor de trˆes notas.
Conceitos: fun ̧c ̃oes e structs.
*/
#include<stdio.h>
#include<stdlib.h>
#include"aluno.h"

int exercicio2(){
  Aluno aluno;
  calcularMedia(&aluno, TAMANHO);
  printf("A media do aluno e: %.2f\n", aluno.media);
  exibirNotas(&aluno, TAMANHO);
  return 0;
}

// int main(){
//   return exercicio2();
// }