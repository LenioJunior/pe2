#include <stdio.h>

typedef struct 
{
    int id;
    int idade;
    char nome[50];
} Pessoa;

void lerDados(Pessoa * pessoa){
    printf("Informe a idade\n");
    scanf("%d", &pessoa->idade);
    printf("Informe o nome\n");
    fgets(pessoa->nome, 50, stdin);
}

Pessoa * inserir(Pessoa * agenda, int * quantidade){
    if(agenda == NULL){
        agenda = malloc(sizeof(Pessoa));
    }
    lerDados(agenda);
    quantidade++;
}

void listar(Pessoa * pessoa, int quantidade){
    
}

void menu(){
    int opcao;
    Pessoa * agenda = NULL;
    int quantidade = 0;

    do
    {
        printf("------------ Agenda ------------\n");
        printf("1-Inserir\n");
        printf("2-Excluir\n");
        printf("3-Editar\n");
        printf("4-Listar\n");
        printf("5-Sair\n");

        printf("Digite a opção\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Inserir\n");
            agenda = inserir(agenda, &quantidade);
            break;
        case 2:
            printf("Excluir\n");
            // excluir();
            break;
        case 3:
            printf("Editar\n");
            // editar();
            break;
        case 4:
            printf("Listar\n");
            // listar();
            break;
        case 5:
            printf("Sair\n");
            return 0;
            break;
        default:
            printf("Opção Inválida!\n");
            break;
        }
    } while (opcao != 5);
}

int main()
{
    menu();
    return 0;
}