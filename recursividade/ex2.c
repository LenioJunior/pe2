#include<stdio.h>
#include<stdlib.h>

/*
Exercício 2: Multiplicação Recursiva Implemente uma função recursiva em C que multiplique 
dois números inteiros positivos sem usar o operador de multiplicação (*) 
e sem utilizar laços (for, while).
mult(a, b) = a + mult(a, b − 1), com base: b = 0 ⇒ 0
• Exemplo de entrada: a = 4, b = 3
• Saída esperada: 12
*/

int inverterString(int op1, int op2){
  if (op2 == 0)
    return 0;

  return op1 + inverterString(op1, op2 - 1);
}

int main(){
  int operador1, operador2;
  printf("Informe dois numeros no formato num1 num2: ");
  scanf("%d %d", &operador1, &operador2);
  int result = inverterString(operador1, operador2);
  printf("Resultado da multiplicacao: %d\n", result);
}