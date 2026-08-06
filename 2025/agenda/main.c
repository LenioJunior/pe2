#include<stdio.h>
#include<stdlib.h>
#include"helpers.h"
#include"agenda.h"


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