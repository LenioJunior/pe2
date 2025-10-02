#include<stdio.h>
#include<stdlib.h>
#include"operacoes.c"

void menu(){
  printf("--- Operacoes Disponiveis ---\n");
  printf("1-Soma\n");
  printf("2-Subtracao\n");
  printf("3-Multiplicacao\n");
  printf("4-Divisao\n");
}

void leOpcao(int * opcao){
  scanf("%d", opcao);
}

void leNumeros(float * num1, float * num2){
  printf("Informe o numero 1:\n");
  scanf("%f", num1);
  printf("Informe o numero 2:\n");
  scanf("%f", num2);
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

int main(){
  int opcao;
  float n1, n2;
  do{
    menu();    
    leOpcao(&opcao); 
    if(opcao != -1){   
      leNumeros(&n1, &n2);
      executaAcao(&opcao, &n1, &n2); 
    }
  } while (opcao != -1);
 
}