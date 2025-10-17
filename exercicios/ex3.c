/*
Exerc ́ıcio 3: Vetor de Structs e Busca

Crie um vetor de 10 alunos e permita ao usu ́ario buscar um aluno pelo n ́umero
de matr ́ıcula, exibindo seus dados.
Conceitos: vetores e busca em structs.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"aluno.h"

#define TAM 3

int buscarAlunoPorMatricula(Aluno alunos[], char * matricula){
  int posicao = -1;

  for (int i = 0; i < TAM; i++)
  {
    if(strcmp(alunos[i].matricula, matricula) == 0){
      posicao = i;
      break;
    }
  }  

  return posicao;
}

int exercicio3 (){
  Aluno * alunos = criar(TAM);  

  strcpy(alunos[0].matricula, "100100");
  strcpy(alunos[0].nome, "Joao");

  strcpy(alunos[0].matricula, "200200");
  strcpy(alunos[1].nome, "Maria");

  strcpy(alunos[0].matricula, "300300");
  strcpy(alunos[2].nome, "Carlos");

  int resultado = buscarAlunoPorMatricula(alunos, "200201");

  if (resultado == -1){
    printf("Não encontrado!\n");
  } else {
    printf("Encontrado na posicao %d. Nome: %s.\n", resultado, alunos[resultado].nome);
  }
  return 0;
}

// int main(){
//   return exercicio3();
// }