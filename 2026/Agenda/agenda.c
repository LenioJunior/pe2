#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    scanf("%d", &pessoa->idade);
}

int isListaVazia(int quantidade)
{
    return quantidade == 0;
}

Pessoa * leArquivo(int * quantidade)
{
    char nomeArquivo[] = "agenda.txt";
    FILE *arquivo = fopen(nomeArquivo, "a");

    if (!arquivo)
    {
        printf("Não foi possível ler o arquivo '%s'.\n", nomeArquivo);
        exit(1);
    }

    int numRegistros = 100;
    int cont = 0;
    char linha[256];
    Pessoa * agenda = malloc(numRegistros * sizeof(Pessoa));

    while (cont < numRegistros && fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        int lidos = sscanf(linha, "%d,%d,%49[^\n]", agenda[cont].id, agenda[cont].idade, agenda[cont].nome);
        if (lidos != 3)
        {
            printf("Erro ao ler a linha '%d' do arquivo!\n", cont + 1);
        }
    }

    *quantidade = cont;

    fclose(arquivo);

    return realloc(agenda, cont);
}

int gravaArquivo(Pessoa *agenda, int quantidade)
{
    // char nomeArquivo[] = "agenda.txt";
    // FILE *arquivo = fopen(nomeArquivo, "+a");
    // if (!arquivo)
    // {
    //     printf("Não foi possível gravar no arquivo '%s'.\n", nomeArquivo);
    //     exit(1);
    // }

    // for (int i = 0; i < quantidade; i++)
    // {
    //     fprintf(arquivo, "%d,%d,%49[^\n]", agenda->id, agenda->idade, agenda->nome);
    // }

    // fclose(arquivo);
    return 0;
}

Pessoa *inserir(Pessoa *agenda, int *quantidade, int *id)
{
    if (!isListaVazia(*quantidade))
    {
        Pessoa *resized = realloc(agenda, ((*quantidade + 1) * sizeof(Pessoa)));
        if (resized == NULL)
        {
            printf("Erro ao realocar a agenda.");
            exit(1);
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

Pessoa *buscarPorId(Pessoa *agenda, int quantidade, int id, int *posicao)
{
    for (int i = 0; i < quantidade; i++)
    {
        if (agenda->id == id)
        {
            *posicao = i;
            return agenda;
        }
        agenda++;
    }
    return NULL;
}

Pessoa *buscarPorNome(Pessoa *agenda, int quantidade, char *nome, int *posicao)
{
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(agenda->nome, nome) == 0)
        {
            *posicao = i;
            return agenda;
        }
        agenda++;
    }
    return NULL;
}

void acaoEditar()
{
    printf("Executei acao editar");
}

void acaoExcluir()
{
    printf("Executei acao excluir");
}

void editar(Pessoa *agenda, int quantidade, void (*acao)())
{
    if (isListaVazia(quantidade))
    {
        printf("Agenda vazia!\n");
    }
    else
    {
        int opcaoBusca = 0;
        Pessoa *pessoa = NULL;
        int posicao = -1;
        do
        {
            printf("Deseja buscar por 1-Id, 2-Nome, 3-Listar, 4-Voltar?\n");
            scanf("%d", &opcaoBusca);
            switch (opcaoBusca)
            {
            case 1:
                printf("Informe um Id para buscar\n");
                int id;
                scanf("%d", &id);
                pessoa = buscarPorId(agenda, quantidade, id, &posicao);
                if (pessoa == NULL)
                {
                    printf("Pessoa com Id '%d' não encontrada!\n", id);
                }
                else
                {
                    listarPessoa(pessoa);
                    lerDados(pessoa);
                    printf("Pessoa Editada com Sucesso!\n");
                }

                break;
            case 2:
                printf("Informe um Nome para buscar\n");
                char nome[50];
                scanf(" %49[^\n]", nome);
                pessoa = buscarPorNome(agenda, quantidade, nome, &posicao);
                if (pessoa == NULL)
                {
                    printf("Pessoa com Nome '%s' não encontrada!\n", nome);
                }
                else
                {
                    acao();
                    listarPessoa(pessoa);
                    lerDados(pessoa);
                    printf("Pessoa Editada com Sucesso!\n");
                }
                break;
            case 3:
                listar(agenda, quantidade);
                break;
            case 4:
                break;
            default:
                printf("Opção Inválida!\n");
                opcaoBusca = -1;
                break;
            }

        } while (opcaoBusca != 4);
    }
}

void excluir(Pessoa *agenda, int *quantidade)
{
    if (isListaVazia(*quantidade))
    {
        printf("Agenda vazia!\n");
    }
    else
    {
        int opcaoBusca = 0;
        Pessoa *pessoa = NULL;
        int posicao = -1;
        do
        {
            printf("Deseja buscar por 1-Id, 2-Nome, 3-Listar, 4-Voltar?\n");
            scanf("%d", &opcaoBusca);
            switch (opcaoBusca)
            {
            case 1:
                printf("Informe um Id para buscar\n");
                int id;
                scanf("%d", &id);
                pessoa = buscarPorId(agenda, *quantidade, id, &posicao);
                if (pessoa == NULL)
                {
                    printf("Pessoa com Id '%d' não encontrada!\n", id);
                }
                else
                {
                    listarPessoa(pessoa);

                    // Excluir
                    Pessoa *busca = pessoa;
                    for (int i = posicao; i < *quantidade - 1; i++)
                    {
                        *busca = *(busca + 1);
                        busca++;
                        posicao++;
                    }
                    (*quantidade)--;

                    if (*quantidade > 0)
                    {
                        busca = realloc(agenda, (*quantidade) * sizeof(Pessoa));
                    }

                    if (busca == NULL)
                    {
                        printf("Erro ao realocar agenda após exclusão!\n");
                        exit(1);
                    }

                    printf("Pessoa Excluída com Sucesso!\n");
                }

                break;
            case 2:
                printf("Informe um Nome para buscar\n");
                char nome[50];
                scanf(" %49[^\n]", nome);
                pessoa = buscarPorNome(agenda, *quantidade, nome, &posicao);
                if (pessoa == NULL)
                {
                    printf("Pessoa com Nome '%s' não encontrada!\n", nome);
                }
                else
                {
                    listarPessoa(pessoa);

                    // Excluir

                    printf("Pessoa Excluída com Sucesso!\n");
                }
                break;
            case 3:
                listar(agenda, *quantidade);
                break;
            case 4:
                break;
            default:
                printf("Opção Inválida!\n");
                break;
            }

        } while (opcaoBusca != 4);
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

    //agenda = leArquivo(&quantidade);

    do
    {
        printf("------------ Agenda ------------\n");
        printf("1-Inserir\n");
        printf("2-Excluir\n");
        printf("3-Editar\n");
        printf("4-Listar\n");
        printf("5-Sair\n");

        printf("Digite a opção\n");
        int resultado = scanf("%d", &opcao);
        // Resultado indica quantos %d foram lidos.
        // Se foi lido 0 em resultado, significa que usuário digitou caracteres.
        if (resultado == 0)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

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
            editar(agenda, quantidade, acaoEditar);
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