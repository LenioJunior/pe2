#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int idade;
    float salario;
} Funcionario;

int main() {
    FILE *arquivo;
    Funcionario f1 = {"Maria da Silva", 28, 5200.50};
    Funcionario f2;
    Funcionario f3 = {"Lenio Oliveira", 30, 1234.56};
    Funcionario f;
    char linha[200];

    // --- Escrita com aspas ---
    arquivo = fopen("funcionario.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "%s;%d;%.2f\n", f1.nome, f1.idade, f1.salario);
    fprintf(arquivo, "%s;%d;%.2f\n", f3.nome, f3.idade, f3.salario);
    fclose(arquivo);

    arquivo = fopen("funcionario.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    
    printf("=== Lista de Funcionários ===\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        size_t len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n')
            linha[len - 1] = '\0';

        if (sscanf(linha, "%49[^;];%d;%f", f.nome, &f.idade, &f.salario) == 3) {
            printf("%-20s | %2d anos | R$%.2f\n", f.nome, f.idade, f.salario);
        } else {
            printf("Linha inválida: %s\n", linha);
        }
    }
    fclose(arquivo);

    return 0;
}
