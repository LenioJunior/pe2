#include<stdio.h>
#include<stdlib.h>
#include"examefinal.h"

void apresentaMenu(){
  printf("-------------- MENU DE QUESTOES --------------\n");
  printf("1 - Questao 1\n");
  printf("2 - Questao 2\n");
  printf("3 - Questao 3\n");
  printf("4 - Questao 4\n");
  printf("-1 - Sair\n");
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
      printf("Executando Questao 1 1\n");
      questao1();
      break;
    case 2:
      printf("Executando Questao 2\n");
      questao2();
      break;
    case 3:
      printf("Executando Questao 3\n");
      questao3();
      break;
    case 4:
      printf("Executando Questao 4\n");
      questao4();
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