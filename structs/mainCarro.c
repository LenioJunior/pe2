
#include<stdio.h>
#include"structCarro.h"

#define QTDE 1

int main() {
  Carro * carros[QTDE];

  for (int i = 0; i < QTDE; i++)
  {
    carros[i] = criar();
  } 
  

  if (carros == NULL) {
    printf("Nao foi possivel alocar a memoria!!!");
    return 1;
  }
 
  for (int i = 0; i < QTDE; i++)
  {
    preenche(carros[i]);
  }
  
  for (int i = 0; i < QTDE; i++)
  {
    exibe(carros[i]);
  }
}