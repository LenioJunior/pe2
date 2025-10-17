/*
Exercício 1: Cadastro de Aluno (Struct B ́asica)

Crie uma struct Aluno com os campos: nome, matrícula e m ́edia. Leia os dados
de 3 alunos e exiba o nome do aluno com a maior m ́edia.
Conceitos: struct b ́asica.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum Curso { COMPUTACAO, ELETRICA, MECATRONICA };

typedef struct pessoa{
  char * nome;
  char * matricula;
  float media;
} Pessoa;

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

void limpaBuffer(){
  while(getchar() != '\n');
}

void lerDadosPessoa(Pessoa * pessoa){
  printf("-------- Lendo dados da pessoa ---------\n");
  printf("Informe o nome:\n");
  pessoa->nome = lerString();
  printf("Informe a matricula:\n");
  pessoa->matricula = lerString();
  printf("Informe a media:\n");
  scanf("%f", &pessoa->media);
  limpaBuffer();
}

void exibeDadosPessoa(Pessoa * pessoa){
  printf("-------- Exibindo os dados da pessoa ---------\n");
  printf("Nome: %sMatricula: %sMedia: %.2f\n",
    pessoa->nome, pessoa->matricula, pessoa->media);
}

int main(){
  int quantidade;
  printf("Informe a quantidade de pessoas a serem lidas\n");
  scanf("%d", &quantidade);

  limpaBuffer();
  
  Pessoa * pessoa = malloc(sizeof(Pessoa) * quantidade);
  if(pessoa == NULL)
    return 1;

  for (int i = 0; i < quantidade; i++)
  {
    lerDadosPessoa(&pessoa[i]);
  }  

  for (int i = 0; i < quantidade; i++)
  {
    exibeDadosPessoa(&pessoa[i]);
  }  
}