
#include<stdio.h>
#include"structCarro.h"

#define QTDE 1

void preenche(Carro * carros){
  for (int i = 0; i < QTDE; i++)
  {
    preenche(carros);
  }
}

int main() {
  Carro * carros[QTDE];

  for (int i = 0; i < QTDE; i++)
  {
    carros[i] = criar();
  } 
  
  preenche(carros);

  if (carros == NULL) {
    printf("Nao foi possivel alocar a memoria!!!");
    return 1;
  }
 
  
  
  for (int i = 0; i < QTDE; i++)
  {
    exibe(carros[i]);
  }
}