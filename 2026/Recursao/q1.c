#include <stdio.h>

void saque(int valor, int notas[], int qtd_notas, int indice) {
    if (valor == 0 || indice == qtd_notas) {
        return;
    }

    int quantidade = valor / notas[indice];

    if (quantidade > 0) {
        printf("%d nota(s) de R$%d\n", quantidade, notas[indice]);
    }

    saque(valor % notas[indice], notas, qtd_notas, indice + 1);
}

int main() {
    int notas[] = {100, 50, 20, 10, 5, 2};
    int qtd_notas = 6;

    saque(287, notas, qtd_notas, 0);

    return 0;
}