#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int idade;
    float salario;
} Funcionario;

int main() {
    FILE *arquivo;
    Funcionario f1 = {"Maria da Silva", 28, 5200.50};
    Funcionario f2;

    // --- Escrita com aspas ---
    arquivo = fopen("funcionario.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Coloca o nome entre aspas
    fprintf(arquivo, "\"%s\" %d %.2f\n", f1.nome, f1.idade, f1.salario);
    fclose(arquivo);

    // --- Leitura preservando as aspas ---
    arquivo = fopen("funcionario.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // %49[^\"] lê até a próxima aspa (sem incluí-la)
    fscanf(arquivo, "\"%49[^\"]\" %d %f", f2.nome, &f2.idade, &f2.salario);
    fclose(arquivo);

    printf("Nome: %s\nIdade: %d\nSalário: %.2f\n",
           f2.nome, f2.idade, f2.salario);

    return 0;
}
