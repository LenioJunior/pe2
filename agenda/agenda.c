#include<stdio.h>
#include<stdlib.h>
#include"agenda.h"

Contato * contatos = NULL;

void limpaBuffer(){
  while(getchar() != '\n');
}

Contato * novoContato(){
  Contato * novo = malloc(sizeof(Contato));
  novo->anterior = NULL;
  novo->proximo = NULL;
  return novo;
}

void lerDadosContato(Contato * contato){
  limpaBuffer();
  printf("Informe o Nome: ");
  fgets(contato->nome, sizeof(contato->nome), stdin);
  printf("Informe o Apelido: ");
  fgets(contato->apelido, sizeof(contato->apelido), stdin);
  printf("Informe o Telefone: ");
  fgets(contato->telefone, sizeof(contato->telefone), stdin);
  printf("Informe o Logradouro: ");
  fgets(contato->endereco.logradouro, sizeof(contato->endereco.logradouro), stdin);
  printf("Informe o Endereço: ");
  fgets(contato->endereco.endereco, sizeof(contato->endereco.endereco), stdin);
  printf("Informe o Numero: ");
  scanf("%d", &contato->endereco.numero);
  printf("Informe o Cep: ");
  fgets(contato->endereco.cep, sizeof(contato->endereco.cep), stdin);
}

FILE * abrirAgenda(char fileName[]){
  return fopen(fileName, "w");
}

int fecharAgenda(FILE * file){
  return fclose(file);
}

void exibirContato(Contato * contato){
  printf("Nome: %s\nApelido: %s\nTelefone: %s\n", contato->nome, contato->apelido, contato->telefone);
  printf("Endereco: %s %s %d, Cep: %s", contato->endereco.logradouro, contato->endereco.endereco, contato->endereco.numero, contato->endereco.cep);
}

void exibirContatos(){
  if(contatos == NULL)
    printf("Não há contatos a serem exibidos.");

  do {
    exibirContato(contatos);
    contatos = contatos->proximo;
  } while(contatos != NULL);
}

int incluirContato(){
  if(contatos == NULL){
    contatos = novoContato();
    lerDadosContato(contatos);
  } else {
    Contato * novo = novoContato();
    lerDadosContato(novo);

    do {
      contatos++;
    } while (contatos->proximo != NULL);

    novo->proximo = contatos->proximo;
    novo->anterior = contatos;
    contatos->proximo = novo;
  }
  
  return 0;
}

int editarContato(){
  return 0;
}

int removerContato(){
  return 0;
}

void buscarContato(){

}
