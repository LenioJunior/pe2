#include<stdio.h>
#include<stdlib.h>

int fatorial(int num){
  if(num == 1){
    return 1;
  }
  return num * fatorial(num - 1);
}

int main(){
  int numero;
  printf("Informe um numero para retornar seu fatorial: ");
  scanf("%d", &numero);
  int result = fatorial(numero);
  printf("Resultado: %d\n", result);
}