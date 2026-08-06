#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]){

  for (int i = 0; i < argc; i++)
  {
    printf("Argumento %d: %s\n", i, argv[i]);
  }
  if (argc < 4){
    printf("Numero de argumentos invalidos!\n");
    return 1;
  }

  int n1 = atoi(argv[1]);
  int n2 = atoi(argv[3]);
  char operacao = * argv[2];
  printf("Os argumentos sao: N1: %d, N2: %d, Operacao: %c\n",
    n1, n2, operacao);

  int result = 0;

  switch (operacao)
  {
  case '+':
    result = n1 + n2;
    break;  
  case '-':
    result = n1 - n2;
    break;  
  case '@':
    result = n1 * n2;
    break;  
  case '/':
    result = n1 / n2;
    break;  
  default:
    break;
  }
  printf("O resultado da operacao e: %d\n", result);
}