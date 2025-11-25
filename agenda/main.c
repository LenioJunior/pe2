#include<stdio.h>
#include<stdlib.h>
#include"helpers.h"
#include"agenda.h"


int main(){
  Contato * contatos = malloc(sizeof(Contato));
  int opcao;
  do {
    apresentaMenu();
    opcao = leOpcao();
    executaOpcao(opcao, contatos, 1);
  } while (opcao != -1);
  printf("Finalizando...");
  return 0;
}