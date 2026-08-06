#include<stdio.h>
#include<stdlib.h>

/*
Exercício 1: Soma de Dígitos Implemente uma funcao recursiva em C que calcule 
a soma dos dígitos de um n ́umero inteiro positivo.

soma(n) = (n mod 10) + soma  (n / 10), com base: n = 0 ⇒ 0

• Exemplo de entrada: n = 357
• Saída esperada: 15 (pois 3 + 5 + 7 = 15)
*/

int somaDigitos(int num){
  if (num == 0)
    return 0;

  return (num % 10) + somaDigitos(num / 10);
}

int main(){
  int numero;
  printf("Informe um numero: ");
  scanf("%d", &numero);
  int result = somaDigitos(numero);
  printf("Resultado: %d\n", result);
}