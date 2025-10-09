#include<stdio.h>
#include"structCarro.h"

struct carro {
  char marca[50];
  char modelo[50];
  int km;
  char combustivel[50];
  int ano;
};

Carro * criar(int quantidade){
  return (Carro *) malloc(sizeof(Carro));
}

void preenche(Carro * carro){
  printf("Informe a marca: \n");
  fgets(carro->marca, 50, stdin);

  printf("Informe o modelo: \n");
  fgets(carro->modelo, 50, stdin);

  printf("Informe o Km: \n");
  scanf("%d ", &carro->km);

  printf("Informe o tipo de combustivel: \n");
  fgets(carro->combustivel, 50, stdin);

  printf("Informe o ano: \n");
  scanf("%d", &carro->ano);
}

void exibe(Carro * carro){
  printf("Informacoes do Carro\n");
  printf("Marca: %s\nModelo: %s\nKm: %d\nCombustivel: %s\nAno: %d\n",
        carro->marca, carro->modelo, carro->km, carro->combustivel, carro->ano);
}