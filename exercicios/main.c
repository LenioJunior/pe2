#include<stdio.h>
#include<stdlib.h>
#include"exercicios.h"

void apresentaMenu(){
  printf("-------------- MENU DE EXERCICIOS --------------\n");
  printf("1 - Exercício 1\n");
  printf("2 - Exercício 2\n");
  printf("3 - Exercício 3\n");
  printf("4 - Exercício 4\n");
  printf("5 - Exercício 5\n");
}

int leOpcao(){
  int opcao;
  printf("\nInforme uma opcao:\n");
  scanf(" %d", &opcao);
  return opcao;
}

void executaOpcao(int opcao){
  switch (opcao)
  {
    case 1:
      printf("Executando Exercício 1\n");
      exercicio1();
      break;
    case 2:
      printf("Executando Exercício 2\n");
      exercicio2();
      break;
    case 3:
      printf("Executando Exercício 3\n");
      exercicio3();
      break;
    case 4:
      printf("Executando Exercício 4\n");
      exercicio4();
      break;
    case 5:
      //printf("Executando Exercício 5");
      //exercicio5();
      break;
    default:
      printf("Opção Inválida");
      break;
    }
}

int main(){
  int opcao;
  do {
    apresentaMenu();
    opcao = leOpcao();
    executaOpcao(opcao);
  } while (opcao != -1);
  printf("Finalizando...");
  return 0;
}