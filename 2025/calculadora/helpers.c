#include<stdlib.h>
#include<stdio.h>
#include"operacoes.h"

void leOpcao(int * opcao){
  scanf("%d", opcao);
}

void leNumeros(float * numero1, float * numero2){
  printf("Informe o numero 1:\n");
  scanf("%f", numero1);
  printf("Informe o numero 2:\n");
  scanf("%f", numero2);
}

void exibeResultado(float * result){
  printf("O resultado é %.2f\n", *result);
}

void executaAcao(int * opcao, float * n1, float * n2){
  float resultado;
  switch (* opcao)
  {
    case 1:
      resultado = soma(*n1, *n2);
      break;
    case 2:
      resultado = subtracao(*n1, *n2);
      break;
    case 3:
      resultado = multiplicacao(*n1, *n2);
      break;
    case 4:
      resultado = divisao(*n1, *n2);
      break;
    default:
      printf("Operacao Invalida!");
  }
  exibeResultado(&resultado);
}