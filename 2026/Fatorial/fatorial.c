#include <stdio.h>

int fatorial(int numero){
    printf("%d\n", numero);
    if(numero == 1){
        return 1;
    }    
    return numero * fatorial(numero - 1);    
}

int main()
{
    int num =0;

    printf("--- Cálculo de Fatorial ---\n");
    printf("Informe um número: \n");
    scanf("%d", &num);

    num = fatorial(num);
    printf("\nResultado: %d\n", num);

    return 0;
}
