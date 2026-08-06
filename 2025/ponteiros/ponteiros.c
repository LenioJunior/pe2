#include<stdio.h>
#include<stdlib.h>

int main(){
  int v = 5;
  int * pv = &v;

  // printf("Valor de V: %d\n", v);
  // printf("Valor de PV: %d\n", * pv);

  // printf("Endereco de V: %p\n", &v);
  // printf("Endereco de PV: %p\n", pv);
  
  // * pv = 6;

  // printf("Valor de V: %d\n", v);
  // printf("Valor de PV: %d\n", * pv);

  int n = 5;
  int x = n;
  int * pn = & n;
  int * op = pn;
  int ** ppp = &op;

  printf("Valor de N: %d\n", n);      // 5 
  printf("Valor de PN: %d\n", * pn);  // 5
  printf("Valor de PPP: %d\n", ** ppp);  // 5

  // printf("Endereco de N: %p\n", &n); //// esse é igual ao de baixo
  // printf("Endereco que PN aponta: %p\n", pn); /// esse aqui
  

  // printf("Endereco onde PN esta: %p\n", &pn); // esse é diferente
  printf("Endereco onde OP esta: %p\n", &op); // esse é diferente
  printf("Endereco que OP aponta: %p\n", op); /// esse aqui
  printf("Endereco onde PPP aponta: %p\n", *ppp); /// esse aqui

  // * pn = 10;
  // printf("Valor de N: %d\n", n);    // 10
  // printf("Valor de PN: %d\n", * pn);// 10
  // printf("Valor de OP: %p\n", * op);// 10

  // n = 20;
  // printf("Valor de N: %d\n", n);      // 20
  // printf("Valor de PN: %d\n", * pn);  // 20

}