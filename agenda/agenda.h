#ifndef AGENDA_H
#define AGENDA_H

#include<stdio.h>
#include<stdlib.h>

typedef struct endereco {
  char logradouro[15];
  char endereco[100];
  int numero;
  char cep[12];
} Endereco;

typedef struct contato {
  char nome[100];
  char apelido[50];
  char telefone[15];
  Endereco endereco;
  struct contato * anterior;
  struct contato * proximo;
} Contato;

FILE * abrirAgenda(char fileName[]);
int fecharAgenda();
void exibirContato(Contato * contato);
void exibirContatos();
int incluirContato();
int editarContato();
int removerContato();
void buscarContato();

#endif