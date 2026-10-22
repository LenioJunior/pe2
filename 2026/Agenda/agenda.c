#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct
{
    int id;
    int idade;
    char nome[50];
} Pessoa;

void listar(Pessoa *pessoa, int quantidade);
void listarPessoa(Pessoa *pessoa);

void lerDados(Pessoa *pessoa)
{
    printf("Informe o nome\n");
    scanf(" %49[^\n]", pessoa->nome);
    printf("Informe a idade\n");
    lerValorNumerico(&pessoa->idade);
}

int isListaVazia(int quantidade)
{
    return quantidade == 0;
}

Pessoa *lerArquivo(int *quantidade)
{
    char nomeArquivo[] = "agenda.txt";
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (!arquivo)
    {
        char error[200];
        snprintf(error, sizeof(error), "Não foi possível ler o arquivo '%s'.\n", nomeArquivo);
        perror(error);
        exit(1);
    }

    int numRegistros = 100;
    char linha[256];

    Pessoa *agenda = malloc(numRegistros * sizeof(Pessoa));
    Pessoa *toLoop = agenda;

    while (*quantidade < numRegistros && fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        int lidos = sscanf(linha, "%d,%d,%49[^\n]", &toLoop->id, &toLoop->idade, toLoop->nome);
        if (lidos != 3)
        {
            printf("Erro ao ler a linha '%d' do arquivo!\n", (*quantidade) + 1);
        }
        toLoop++;
        (*quantidade)++;
    }

    fclose(arquivo);

    if (*quantidade > 0)
    {
        return realloc(agenda, (*quantidade) * sizeof(Pessoa));
    }
    else
    {
        return NULL;
    }
}

void gravaArquivo(Pessoa *agenda, int quantidade)
{
    char nomeArquivo[] = "agenda.txt";
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo)
    {
        char error[200];
        snprintf(error, sizeof(error), "Não foi possível gravar no arquivo '%s'.\n", nomeArquivo);
        perror(error);
        exit(1);
    }

    for (int i = 0; i < quantidade; i++)
    {
        fprintf(arquivo, "%d,%d,%s\n", agenda->id, agenda->idade, agenda->nome);
        agenda++;
    }

    fclose(arquivo);
}

void lerValorNumerico(int * numero)
{
    int resultado = scanf("%d", numero);
    
    // Resultado indica quantos %d foram lidos.
    // Se foi lido 0 em resultado, significa que usuário digitou caracteres ao invés de números.
    if (resultado == 0)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

Pessoa *inserir(Pessoa *agenda, int *quantidade, int *id)
{
    if (!isListaVazia(*quantidade))
    {
        Pessoa *resized = realloc(agenda, ((*quantidade + 1) * sizeof(Pessoa)));
        if (resized == NULL)
        {
            printf("Erro ao realocar a agenda.");
            return agenda;
        }
        agenda = resized;
    }
    Pessoa *ultimaPosicao = agenda + *quantidade;

    lerDados(ultimaPosicao);
    (*quantidade)++;
    ultimaPosicao->id = *id;
    (*id)++;
    return agenda;
}

int buscarPorId(Pessoa *agenda, int quantidade, int id)
{
    for (int indice = 0; indice < quantidade; indice++)
    {
        if (agenda->id == id)
        {
            return indice;
        }
        agenda++;
    }
    return -1;
}

int buscarPorNome(Pessoa *agenda, int quantidade, char *nome)
{
    for (int indice = 0; indice < quantidade; indice++)
    {
        if (strcmp(agenda->nome, nome) == 0)
        {
            return indice;
        }
        agenda++;
    }
    return -1;
}

int acoesDeBusca(Pessoa *agenda, int quantidade)
{
    int posicaoEncontrada = -1;
    if (isListaVazia(quantidade))
    {
        printf("Agenda vazia!\n");
        return posicaoEncontrada;
    }
    else
    {
        int opcaoBusca = 0;
        do
        {
            printf("Deseja buscar por 1-Id, 2-Nome, 3-Listar, 4-Voltar?\n");
            lerValorNumerico(&opcaoBusca);

            switch (opcaoBusca)
            {
            case 1:
                printf("Informe um Id para buscar\n");
                int id;
                lerValorNumerico(&id);

                posicaoEncontrada = buscarPorId(agenda, quantidade, id);
                if (posicaoEncontrada != -1)
                {
                    return posicaoEncontrada;
                }
                printf("Pessoa com Id '%d' não encontrada!\n", id);
                break;
            case 2:
                printf("Informe um Nome para buscar\n");
                char nome[50];
                scanf(" %49[^\n]", nome);
                posicaoEncontrada = buscarPorNome(agenda, quantidade, nome);
                if (posicaoEncontrada != -1)
                {
                    return posicaoEncontrada;
                }
                printf("Pessoa com Nome '%s' não encontrada!\n", nome);
                break;
            case 3:
                listar(agenda, quantidade);
                break;
            case 4:
                break;
            default:
                printf("Opção Inválida!\n");
                break;
            }

        } while (opcaoBusca != 4);
    }
    return posicaoEncontrada;
}

void editar(Pessoa *agenda, int quantidade)
{
    int posicaoEncontrada = acoesDeBusca(agenda, quantidade);
    if (posicaoEncontrada != -1)
    {
        Pessoa *pessoaEncontrada = agenda + posicaoEncontrada;
        listarPessoa(pessoaEncontrada);
        lerDados(pessoaEncontrada);
        printf("\n--- Pessoa Editada com Sucesso! ---\n");
    }
}

Pessoa *moverElementosAposExcluido(Pessoa *agenda, int *quantidade, int posicaoEncontrada)
{
    Pessoa *registrosMovidos = agenda + posicaoEncontrada;
    for (int i = posicaoEncontrada; i < *quantidade - 1; i++)
    {
        *registrosMovidos = *(registrosMovidos + 1);
        registrosMovidos++;
        posicaoEncontrada++;
    }
    (*quantidade)--;

    if (*quantidade > 0)
    {
        registrosMovidos = realloc(agenda, (*quantidade) * sizeof(Pessoa));
    }

    if (registrosMovidos == NULL)
    {
        printf("Erro ao realocar agenda após exclusão!\n");
        exit(1);
    }
    return registrosMovidos;
}

void excluir(Pessoa *agenda, int *quantidade)
{
    int posicaoEncontrada = acoesDeBusca(agenda, *quantidade);
    if (posicaoEncontrada != -1)
    {
        Pessoa *pessoaEncontrada = agenda + posicaoEncontrada;
        listarPessoa(pessoaEncontrada);
        moverElementosAposExcluido(agenda, quantidade, posicaoEncontrada);
        printf("\n--- Pessoa Excluída com Sucesso! ---\n");
    }
}

void listarPessoa(Pessoa *pessoa)
{
    printf("Id: %d. Idade: %d. Nome: %s\n", pessoa->id, pessoa->idade, pessoa->nome);
}

void listar(Pessoa *pessoa, int quantidade)
{
    if (isListaVazia(quantidade))
    {
        printf("Agenda vazia!\n");
    }
    else
    {
        printf("--- Exibindo itens da agenda ---\n");
        for (int i = 0; i < quantidade; i++)
        {
            listarPessoa(pessoa);
            pessoa++;
        }
        printf("\n------------------------------\n");
    }
}

void menu()
{
    int opcao;
    Pessoa *agenda = malloc(sizeof(Pessoa));

    if (agenda == NULL)
    {
        printf("Erro ao criar a agenda!\n");
        exit(1);
    }

    int quantidade = 0;
    int id = 1;

    Pessoa *lido = lerArquivo(&quantidade);

    if (lido != NULL)
    {
        agenda = lido;
        id = (lido + quantidade - 1)->id + 1;
    }

    do
    {
        printf("------------ Agenda ------------\n");
        printf("1-Inserir\n");
        printf("2-Excluir\n");
        printf("3-Editar\n");
        printf("4-Listar\n");
        printf("5-Sair\n");

        printf("Digite a opção\n");
        lerValorNumerico(&opcao);

        switch (opcao)
        {
        case 1:
            printf("Inserir\n");
            agenda = inserir(agenda, &quantidade, &id);
            printf("Pessoa Inserida com Sucesso!\n");
            gravaArquivo(agenda, quantidade);
            break;
        case 2:
            printf("Excluir\n");
            excluir(agenda, &quantidade);
            gravaArquivo(agenda, quantidade);
            break;
        case 3:
            printf("Editar\n");
            editar(agenda, quantidade);
            gravaArquivo(agenda, quantidade);
            break;
        case 4:
            printf("Listar\n");
            listar(agenda, quantidade);
            break;
        case 5:
            printf("Sair\n");
            opcao = 5;
            break;
        default:
            printf("Opção Inválida!\n");
            opcao = -1;
            break;
        }
    } while (opcao != 5);
}

int main()
{
    menu();
    return 0;
}