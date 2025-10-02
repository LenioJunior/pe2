#include<stdio.h>
#include<stdlib.h>

int main(){
  int matriz [5][4];

  printf("Size of int: %d\n", sizeof(int));
  printf("Size of char: %d\n", sizeof(char));
  printf("Size of float: %d\n", sizeof(float));
  printf("Size of double: %d\n\n\n", sizeof(double));

  int idade;
  scanf("%d", &idade);

  // for (int linha = 0; linha < 5; linha++)
  // {
  //   for (int coluna = 0; coluna < 4; coluna++){
  //     int valor = ( linha * 4) + coluna + 1;
  //     matriz[linha][coluna] = valor;
  //     printf("Posicao %d: %d\n", valor, matriz[linha][coluna]);
  //   }
  // }
}