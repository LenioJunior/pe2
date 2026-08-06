#include<stdio.h>
#include"operacoes.h"
#include"helpers.h"
#include"vetores.c"

void menu(){
  printf("--- Operacoes Disponiveis ---\n");
  printf("1-Soma\n");
  printf("2-Subtracao\n");
  printf("3-Multiplicacao\n");
  printf("4-Divisao\n");
}

int main(){

  int opcao;
  float rr = soma1(1, 2);
  printf("A soma e: %.2f", rr);
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