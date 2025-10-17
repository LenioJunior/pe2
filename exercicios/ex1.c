/*
Exercício 1: Cadastro de Aluno (Struct Básica)

Crie uma struct Aluno com os campos: nome, matrícula e m ́edia. Leia os dados
de 3 alunos e exiba o nome do aluno com a maior m ́edia.
Conceitos: struct b ́asica.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"aluno.h"

void limpaBuffer(){
  while(getchar() != '\n');
}

int tamanhoString(char * string){
  int tamanho = 0;

  do {
    string++;
    tamanho++;  
  } while (*string != '\0'); 

  return tamanho;
}

char * lerString(){
  char string[100];
  fgets(string, 100, stdin);
  int tamanho = tamanhoString(string);
  char * novaString = malloc(sizeof(char) * tamanho);
  strcpy(novaString, string);
  return novaString;
}

void lerDadosAluno(Aluno * aluno){
  printf("-------- Lendo dados da aluno ---------\n");
  printf("Informe o nome:\n");
  aluno->nome = lerString();
  printf("Informe a matricula:\n");
  aluno->matricula = lerString();
  printf("Informe a media:\n");
  scanf("%f", &aluno->media);
  limpaBuffer();
}

void exibeDadosAluno(Aluno * aluno){
  printf("-------- Exibindo os dados da aluno ---------\n");
  printf("Nome: %sMatricula: %sMedia: %.2f\n",
    aluno->nome, aluno->matricula, aluno->media);
}

int exercicio1(){
  int quantidade;
  printf("Informe a quantidade de alunos a serem lidas\n");
  scanf("%d", &quantidade);

  limpaBuffer();
  
  Aluno * aluno = criar(quantidade);
  if(aluno == NULL)
    return 1;

  for (int i = 0; i < quantidade; i++)
  {
    lerDadosAluno(&aluno[i]);
  }  

  for (int i = 0; i < quantidade; i++)
  {
    exibeDadosAluno(&aluno[i]);
  }
  return 0;
}

// int main(){
//   return exercicio1();
// }