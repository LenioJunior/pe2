#include<stdio.h>

typedef enum cor {
  AZUL = 10,
  AMARELO = 20,
  PRETO = 30
} Cor;

char * obtemCor(enum cor cor){
  switch (cor)
  {
  case 10:
    return "Azul\n";
  case 20:
    return "Amarelo\n";  
  case 30:
    return "Preto\n";  
  default:
    break;
  }
}

int main(){
  Cor cor = AZUL;
  printf("Cor: %s\n\n\n", obtemCor(cor));

  cor = PRETO;
  printf("Cor: %s\n\n\n", obtemCor(cor));

  int numeroCor;
  printf("Informe uma cor (10, 20 ou 30): ");
  scanf("%d", &numeroCor);
  Cor corLida = numeroCor;
  printf("Cor Lida: %s\n", obtemCor(corLida));
}