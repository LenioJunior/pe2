#include<stdio.h>
#include<stdlib.h>

int print()
{
    int *ponteiro, **ponteiroDoPonteiro, valor;
    valor = 50;
    ponteiro = &valor;
    ponteiroDoPonteiro = &ponteiro;

    printf("\nValor de ponteiroDoPonteiro: %p\n", ponteiroDoPonteiro);
    printf("\nEndereço de memoria de ponteiroDoPonteiro: %p\n", &ponteiroDoPonteiro);

    printf("\nEndereço de memoria de ponteiro: %p\n", &ponteiro);
    printf("\nValor de ponteiro: %p\n", ponteiro);

    printf("\nEndereco de memoria de valor: %p\n", &valor);    
    printf("\nValor: %d\n", valor);

    return 0;
}

int main(){
    print();

    return 0;
}