#include<stdio.h>
#include<stdlib.h>

/*
Exercício 3: Inversão de String 
Implemente uma funçao recursiva em C que inverta uma string 
(sem usar funçoes prontas como strrev).

A ideia  ́e inverter o primeiro e o ́ultimo caractere e chamar a funçao
para o trecho restante da string, até que o índice inicial seja maior ou
igual ao final.

• Exemplo de entrada: “computador”
• Saída esperada: “rodatupmoc”
*/

char * inverterString(char * palavra, int ind1, int ind2){
  if (ind1 >= ind2)
    return 0;

  char temp = palavra[ind1];
  palavra[ind1] = palavra[ind2];
  palavra[ind2] = temp;
  return inverterString(palavra, ++ind1, --ind2);
}

int main(){
  char string [50]; // = {'p', 'a', 'l', 'a', 'v', 'r', 'a'};
  printf("Informe uma string a ser invertida: ");
  fgets(string, 50, stdin);
  int tamanhoString;
  for (tamanhoString = 0; tamanhoString < 50; tamanhoString++)
  {
    if(string[tamanhoString] == '\n'){
      tamanhoString -= 1;
      break;
    }
  }
  
  inverterString(string, 0, tamanhoString);
  printf("String invertida: %s\n", string);
}