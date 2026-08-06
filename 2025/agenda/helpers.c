#include<stdio.h>
#include<stdlib.h>
#include"agenda.h"

int leOpcao(){
  int opcao;
  printf("\nInforme uma opcao:\n");
  scanf(" %d", &opcao);
  return opcao;
}

void apresentaMenu(){
  printf("-------------- Agenda de Contatos --------------\n");
  printf("1 - Exibir Contatos\n");
  printf("2 - Incluir Contato\n");
  printf("3 - Editar Contato\n");
  printf("4 - Remover Contato\n");
  printf("5 - Buscar Contato\n");
  printf("6 - Sair\n");
}

void executaOpcao(int opcao){
  switch (opcao)
  {
    case 1:
      printf("Exibir Contatos\n");
      exibirContatos();
      break;
    case 2:
      printf("Incluir Contato\n");
      incluirContato();
      break;
    case 3:
      printf("Editar Contato\n");
      editarContato();
      break;
    case 4:
      printf("Remover Contato\n");
      removerContato();
      break;
    case 5:
      printf("Buscar Contato");
      buscarContato();
      break;
    default:
      printf("Opção Inválida");
      break;
    }
}