#include<stdio.h>
#include<stdlib.h>
#include"vetor.h"

#define TAM 3

float soma(float n1, float n2);
float subtracao(float n1, float n2);
float multiplicacao(float n1, float n2);
float divisao(float n1, float n2);

float soma(float n1, float n2){
  return n1 + n2;
}

float subtracao(float n1, float n2){
  return n1 - n2;
}

float multiplicacao(float n1, float n2){
  return n1 * n2;
}

float divisao(float n1, float n2){
  return n1 / n2;
}
