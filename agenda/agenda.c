#include<stdio.h>
#include<stdlib.h>
#include"agenda.h"

Contato * contatos = NULL;

#define fileName "agenda.txt"

void limpaBuffer(){
  while(getchar() != '\n');
}

int carregarDoArquivo(){
  FILE * file = abrirAgenda();

  if(file == NULL){
    printf("Não foi possível abrir a agenda!\n");
    return 1;
  }

  Contato * contato = novoContato();

  do {
    int count = fread(contato, sizeof(Contato), 1, file);
    if (count != 1){
      printf("Erro ao efetuar a leitura do contato do arquivo!\n");
      return -1;
    }
    if(contatos == NULL){
      contatos = contato;
    } else {
      contatos->proximo
    }
  } while (1);

  fecharAgenda(file);
}

Contato * novoContato(){
  Contato * novo = malloc(sizeof(Contato));
  novo->preenchido = 0;
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
  contato->preenchido = 1;
}

FILE * abrirAgenda(){
  return fopen(fileName, "w");
}

int fecharAgenda(FILE * file){
  return fclose(file);
}

void exibirContato(Contato * contato){
  printf("Contato: %p\n", contato);
  printf("preenchido: %d\n", contato->preenchido);
  if(contato->preenchido){
    printf("Nome: %s\nApelido: %s\nTelefone: %s\n", contato->nome, contato->apelido, contato->telefone);
    printf("Endereco: %s %s %d, Cep: %s", contato->endereco.logradouro, contato->endereco.endereco, contato->endereco.numero, contato->endereco.cep);
  }
}

void exibirContatos(){
  if(contatos == NULL){
    printf("Não há contatos a serem exibidos.\n");
    return;
  }

  do {
    exibirContato(contatos);
    contatos = contatos->proximo;
  } while(contatos != NULL);
}

void addNosContatos(Contato * contato){

}

int incluirContato(){
  Contato * novo;
  if(contatos == NULL){
    contatos = novoContato();
    novo = contatos;
  } else {
    novo = novoContato();
  }
  
  lerDadosContato(novo);
  printf("Contato Lido!\n");
  while (contatos->proximo != NULL) {
    contatos++;
  } 

  if(novo != contatos){
    printf("Contato adicionado apos o contato: %s\n", contatos->nome);
    novo->proximo = contatos->proximo;
    novo->anterior = contatos;
    contatos->proximo = novo;
  }

  FILE * file = abrirAgenda();
  printf("Agenda aberta!\n");
  int count = fwrite(novo, sizeof(Contato), 1, file);
  if(count != 1){
    printf("Ocorreu um erro ao gravar o contato.\n");
    return 1;
  }
  printf("Contato gravado com sucesso!.\n");
  fecharAgenda(file);
  
  
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
