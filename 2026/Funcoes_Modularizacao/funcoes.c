#include<stdio.h>
#include"funcoes.h"

int soma(){
    printf("Eu sou a soma\n");
    subtracao();
}

int subtracao(int num){
    printf("Eu sou a subtracao\n");    
    return num;
}