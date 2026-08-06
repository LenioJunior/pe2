#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"
#include <locale.h>  /* Para usar os acentos na linguagem portuguesa */
#include <wchar.h>   /* Útil pra acentos */
#ifdef _WIN32
#include <windows.h> /* Só pro Windows, pra mudar o codepage do console */
#endif

/* Vetores Dinamicos (structs ) */
Usuario *usuarios = NULL;
int totalusuarios = 0;             /* Vetor de usuario, qts usuarios, e tamanho do vetor alocado */
int capacidadeUsuarios = 0;

Criptomoeda *criptos = NULL;     /* Vet de Criptomoedas */
int totalCriptos = 0;
int capacidadeCriptos = 0;

/* Aplicando funções de auxilio */
void limparTela() {
    system("cls || clear");
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void adicionarUsuario() {
    if (totalusuarios == capacidadeUsuarios) {  /* Para aumentar o tamanho do vet de usuarios */
        int novaCapacidade = (capacidadeUsuarios == 0) ? 1 : capacidadeUsuarios * 2;  /* Para dobrar o valor de vetor */
        Usuario *novoVetor = (Usuario*) realloc(usuarios, novaCapacidade * sizeof(Usuario));
        
        if (novoVetor == NULL) {
            printf("Erro de memória! Não deu pra alocar.\n");
            return;
        }
        
        usuarios = novoVetor;
        capacidadeUsuarios = novaCapacidade;
    }

    Usuario *u = &usuarios[totalusuarios];  /* Ponteiros para novos usuarios */

    u->id = totalusuarios + 1;
    printf("Nome: ");
    fgets(u->nome, 50, stdin);
    u->nome[strcspn(u->nome, "\n")] = '\0';

    printf("E-mail: ");
    fgets(u->email, 70, stdin);
    u->email[strcspn(u->email, "\n")] = '\0';

    printf("Saldo inicial em USD: ");
    scanf("%f", &u->saldoUSD);
    getchar();

    u->totalTransacoes = 0;  /* Para começar sem transações */

    totalusuarios++;
    printf("\nUsuário cadastrado com sucesso! ID = %d\n", u->id);
}

void listaUsuarios() {
    if (totalusuarios == 0) {
        printf("nenhum usuário cadastrado ainda...\n");
        return;  
    }

    printf("\n==== LISTA DE USUÁRIOS ====\n");
    for (int i = 0; i < totalusuarios; i++) {
        Usuario *u = &usuarios[i];  /* Aqui o ponteiro para o usuario atual */

        printf("ID: %d\n", u->id);
        printf("Nome: %s\n", u->nome);
        printf("E-Mail: %s\n", u->email);
        printf("Saldo USD: %.2f\n", u->saldoUSD);  
        printf("Transações: %d\n", u->totalTransacoes);
        printf("-------------------------------\n");
    }
}

void buscarUsuario() {
    int escolha;
    printf("\nBuscar por: 1 - ID | 2 - Nome: ");
    if (scanf("%d", &escolha) != 1) {  /*Se scanf falhar*/
        printf("Entrada inválida! Tenta de novo.\n");
        while (getchar() != '\n');  /* Limpa buffer completamente */
        return;
    }
    while (getchar() != '\n');  /* Limpando o \n sobrando do scanf */

    if (escolha == 1) {
        int idBusca;
        printf("Digite o ID: ");
        if (scanf("%d", &idBusca) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n');
            return;
        }
        while (getchar() != '\n');

        for (int i = 0; i < totalusuarios; i++) {
            Usuario *u = &usuarios[i];
            if (u->id == idBusca) {
                printf("\n===== USUÁRIO ENCONTRADO =====\n");
                printf("ID: %d\n", u->id);
                printf("Nome: %s\n", u->nome);
                printf("E-mail: %s\n", u->email);
                printf("Saldo USD: %.2f\n", u->saldoUSD);  
                printf("Transações: %d\n", u->totalTransacoes);
                return;
            }
        }
        printf("Usuário com ID %d não encontrado!\n", idBusca);
    } else if (escolha == 2) {
        char nomeBusca[50];
        printf("Digite o nome: ");
        fgets(nomeBusca, 50, stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        for (int i = 0; i < totalusuarios; i++) {
            Usuario *u = &usuarios[i];
            if (strcmp(u->nome, nomeBusca) == 0) {
                printf("\n===== USUÁRIO ENCONTRADO =====\n");
                printf("ID: %d\n", u->id);
                printf("Nome: %s\n", u->nome);
                printf("E-mail: %s\n", u->email);
                printf("Saldo USD: %.2f\n", u->saldoUSD);  
                printf("Transações: %d\n", u->totalTransacoes);
                return;
            }
        }
        printf("Usuário com nome '%s' não encontrado!\n", nomeBusca);
    } else {
        printf("Opção inválida!\n");
    }
}

void editarUsuario() {
    int idBusca;
    printf("\nDigite o ID do Usuário a editar: ");
    if (scanf("%d", &idBusca) != 1) {
        printf("Entrada Invalida!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Usuario *u = NULL;  /* Coloquei um ponteiro para o usuario editar */
    for (int i = 0; i < totalusuarios; i++) {
        if (usuarios[i].id == idBusca) {
            u = &usuarios[i];
            break;  /* Para fazer a busca e achar com o ponteiro */
        }
    }

    if (u == NULL) {
        printf("Usuário com o ID %d não Encontrado!\n", idBusca);
        return;
    }

    printf("Novo Nome (atual %s): ", u->nome);  /* Agora vamos editar os campos */
    fgets(u->nome, 50, stdin);
    u->nome[strcspn(u->nome, "\n")] = '\0';

    printf("Novo Email (atual %s): ", u->email);
    fgets(u->email, 70, stdin);
    u->email[strcspn(u->email, "\n")] = '\0';

    printf("Novo Saldo USD (atual %.2f): ", u->saldoUSD);
    scanf("%f", &u->saldoUSD);
    while (getchar() != '\n');

    printf("\nUsuário ID %d atualizado com sucesso!\n", u->id);
}

void removerUsuario() {
    int idBusca;
    printf("\nDigite o ID do Usuário a remover: ");
    if (scanf("%d", &idBusca) != 1) {
        printf("Entrada invalida!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    int index = -1;  /* Aqui coloquei um indice -1 do usuario a ser removido */
    for (int i = 0; i < totalusuarios; i++) {
        if (usuarios[i].id == idBusca) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Usuario com ID %d não Encontrado!\n", idBusca);
        return;
    }

    /* Removendo os elementos pra esquerda com uso de ponteiros */
    for (int i = index; i < totalusuarios - 1; i++) {
        Usuario *atual = &usuarios[i];
        Usuario *proximo = &usuarios[i + 1];
        *atual = *proximo;  /* Copia o proximo para atual, manipulação de ponteiro */
    }

    totalusuarios--;  /* Diminuindo o contador */

    if (totalusuarios < capacidadeUsuarios / 2 && capacidadeUsuarios > 1) {  /* Aqui diminui a capacidade se tiver muito vazio */
        capacidadeUsuarios /= 2;
        usuarios = (Usuario*) realloc(usuarios, capacidadeUsuarios * sizeof(Usuario));
        if (usuarios == NULL && totalusuarios > 0) {
            printf("Erro ao realocar Memória ao remover\n");
            return;
        }
    }

    printf("\nUsuário ID %d Removido com Sucesso!\n", idBusca);
}

void comprarCriptomoeda() {
    int idUsuario, idCripto;
    float quantidade;

    printf("\nDigite o ID do Usuário: ");
    if (scanf("%d", &idUsuario) != 1) {
        printf("Entrada inválida!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Usuario *u = NULL;
    for (int i = 0; i < totalusuarios; i++) {
        if (usuarios[i].id == idUsuario) {
            u = &usuarios[i];  /* Criei um ponteiro para apontar para usuario */
            break;
        }
    }
    if (u == NULL) {
        printf("Usuário ID %d não Encontrado!\n", idUsuario);
        return;
    }

    printf("Criptos Disponíveis:\n");
    for (int i = 0; i < totalCriptos; i++) {
        Criptomoeda *c = &criptos[i];  /* Criei um ponteiro agora para cripto */
        printf("ID: %d - %s (%s) - Preço USD: %.2f\n", c->id, c->nome, c->simbolo, c->precoAtual);  
    }
    
    printf("Digite o ID da Cripto: ");
    if (scanf("%d", &idCripto) != 1) {
        printf("Entrada Invalida!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Criptomoeda *criptoSelecionada = NULL;
    for (int i = 0; i < totalCriptos; i++) {
        if (criptos[i].id == idCripto) {
            criptoSelecionada = &criptos[i];
            break;
        }
    }
    if (criptoSelecionada == NULL) {
        printf("Cripto ID %d não Encontrada!\n", idCripto);
        return;
    }

    printf("Digite a Quantidade a ser Comprada: ");
    if (scanf("%f", &quantidade) != 1 || quantidade <= 0) {
        printf("Quantidade Invalida\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    float valorTotal = quantidade * criptoSelecionada->precoAtual;
    if (valorTotal > u->saldoUSD) {
        printf("Saldo Insuficiente! Você Precisa de %.2f USD, mas tem Atualmente %.2f USD.\n", valorTotal, u->saldoUSD);  
        return;
    }

    if (u->totalTransacoes >= 100) {
        printf("Historico de Transações está Cheio!\n");
        return;
    }

    Transacao *t = &u->historico[u->totalTransacoes];  /* Nova transação usando ponteiro */
    t->idTransacao = u->totalTransacoes + 1;
    t->idCripto = idCripto;
    t->quantidade = quantidade;
    t->valorUSD = valorTotal;
    strcpy(t->tipo, "COMPRA");
    strcpy(t->data, "25/11/2025");  /* Usando data fake */

    u->totalTransacoes++;
    u->saldoUSD -= valorTotal;

    printf("\nCompra Realizada com Sucesso! %.2f %s por %.2f USD.\n", quantidade, criptoSelecionada->simbolo, valorTotal);
}

void venderCriptomoeda() {
    int idUsuario, idCripto;
    float quantidade;

    printf("\nDigite o ID do Usuário: ");
    if (scanf("%d", &idUsuario) != 1) {
        printf("Entrada Invalida!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Usuario *u = NULL;
    for (int i = 0; i < totalusuarios; i++) {
        if (usuarios[i].id == idUsuario) {
            u = &usuarios[i];
            break;
        }
    }
    if (u == NULL) {
        printf("Usuario ID %d não Encontrado!\n", idUsuario);
        return;
    }

    printf("Criptos Disponíveis Para a Venda:\n");
    for (int i = 0; i < totalCriptos; i++) {
        Criptomoeda *c = &criptos[i];
        printf("ID: %d - %s (%s) - Preço USD: %.2f\n", c->id, c->nome, c->simbolo, c->precoAtual);  
    }

    printf("Digite o ID da Criptomoeda: ");
    if (scanf("%d", &idCripto) != 1) {
        printf("Entrada Inválida!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Criptomoeda *criptoSelecionada = NULL;
    for (int i = 0; i < totalCriptos; i++) {
        if (criptos[i].id == idCripto) {
            criptoSelecionada = &criptos[i];
            break;
        }
    }
    if (criptoSelecionada == NULL) {
        printf("Cripto ID %d Não Encontrada!\n", idCripto);
        return;
    }

    printf("Digite a Quantidade a Ser Vendida: ");
    if (scanf("%f", &quantidade) != 1 || quantidade <= 0) {
        printf("Quantidade Inválida...\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    float valorTotal = quantidade * criptoSelecionada->precoAtual;
    
    if (u->totalTransacoes >= 100) {
        printf("Histórico de Transação Está Cheio!\n");
        return;
    }

    Transacao *t = &u->historico[u->totalTransacoes];
    t->idTransacao = u->totalTransacoes + 1;
    t->idCripto = idCripto;
    t->quantidade = -quantidade;  /* Aqui o sinal de negativo é para a venda ser registrada */
    t->valorUSD = valorTotal;
    strcpy(t->tipo, "VENDA");
    strcpy(t->data, "01/12/2025");  /* Data ficticia  */

    u->totalTransacoes++;
    u->saldoUSD += valorTotal;

    printf("\nVenda Realizada! %.2f %s por %.2f USD.\n", quantidade, criptoSelecionada->simbolo, valorTotal);
}

void verCarteira() {
    int idUsuario;
    printf("\nDigite o ID do Usuário: ");
    if (scanf("%d", &idUsuario) != 1) {
        printf("Entrada Invalida!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Usuario *u = NULL;
    for (int i = 0; i < totalusuarios; i++) {
        if (usuarios[i].id == idUsuario) {
            u = &usuarios[i];
            break;
        }
    }
    if (u == NULL) {
        printf("Usuário ID %d não Encontrado!\n", idUsuario);
        return;
    }

    printf("\n #### CARTEIRA DE %s ####\n", u->nome);
    printf("Saldo USD: %.2f\n", u->saldoUSD);  
    printf("Total de Transações: %d\n", u->totalTransacoes);
    printf("Histórico:\n");

    for (int i = 0; i < u->totalTransacoes; i++) {
        Transacao *t = &u->historico[i];  /* Um ponteiro para colocar na transação do vet */
        Criptomoeda *c = NULL;
        for (int j = 0; j < totalCriptos; j++) {
            if (criptos[j].id == t->idCripto) {
                c = &criptos[j];  /* Um ponteiro para cryptomoedas que será relacionada */
                break;
            }
        }
        if (c != NULL) {
            printf("%s - %s: %.2f %s por %.2f USD (%s)\n", t->data, t->tipo, t->quantidade, c->simbolo, t->valorUSD, c->nome);
        } else {
            printf("%s - %s: ID Cripto %d Desconhecido\n", t->data, t->tipo, t->idCripto);
        }
    }
}

/* Função principal */
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");  /* Usado com include locale para a lingua portuguesa */
    carregarDadosBinario();  /* Para carregar os dados ao iniciar */
    

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  /* Fazer com que o windows use utf-8 */
    SetConsoleCP(CP_UTF8);  /* Input */
#endif

    int opcao;

    if (totalCriptos == 0) {  
        capacidadeCriptos = 5;
        criptos = (Criptomoeda*) malloc(capacidadeCriptos * sizeof(Criptomoeda));
        totalCriptos = 3;

        criptos[0].id = 1;
        strcpy(criptos[0].nome, "Bitcoin");
        strcpy(criptos[0].simbolo, "BTC");
        criptos[0].precoAtual = 84574.24f;

        criptos[1].id = 2;
        strcpy(criptos[1].nome, "Ethereum");
        strcpy(criptos[1].simbolo, "ETH");
        criptos[1].precoAtual = 2748.94f;

        criptos[2].id = 3;
        strcpy(criptos[2].nome, "Solana");
        strcpy(criptos[2].simbolo, "SOL");
        criptos[2].precoAtual = 127.28f;
    }

    do {
        limparTela();
        printf("=============================================\n");
        printf("   CRYPTO WALLET - SISTEMA DE CADASTRO      \n\n");
        printf("1. Adicionar Usuários\n");
        printf("2. Listar Usuários\n");
        printf("3. Buscar Usuário\n");
        printf("4. Editar Usuário\n");
        printf("5. Remover Usuário\n");
        printf("6. Comprar Criptomoeda\n");
        printf("7. Vender Criptomoeda\n");
        printf("8. Ver Carteira de um Usuário\n");
        printf("9. Gerar Relatório\n");
        printf("0. Sair\n");
        printf("Escolha uma das Opções: ");
        scanf("%d", &opcao);
        getchar();  /* Para limpar o buffer depois */

        switch (opcao) {
            case 1:
                printf("\n>>> Adicionar novo usuário <<<\n");
                adicionarUsuario();
                pausar();
                break;

            case 2:
                printf("\n>>> Lista de usuários <<<\n");
                listaUsuarios();
                pausar();
                break;

            case 3:
                printf("\n>>> Buscar Usuário <<<\n");
                buscarUsuario();
                pausar();
                break;

            case 4:
                printf("\n>>> Editar Usuário <<<\n");
                editarUsuario();
                pausar();
                break;

            case 5:
                printf("\n>>> Remover Usuário <<<\n");
                removerUsuario();
                pausar();
                break;

            case 6:
                printf("\n>>> Comprar Criptomoedas <<<\n");
                comprarCriptomoeda();
                pausar();
                break;

            case 7:
                printf("\n>>> Vender Criptomoeda <<<\n");
                venderCriptomoeda();
                pausar();
                break;

            case 8:
                printf("\n>>> Ver Carteira do Usuário <<<\n");
                verCarteira();
                pausar();
                break;

            case 9:
                printf("\n>>> Gerar Relatório <<<\n");
                gerarRelatorioTextual();
                pausar();
                break;

            case 0:
                printf("\nSaindo...\n");
                salvarDadosBinario();  /* Add Salvar antes de sair */
                break;

            default:
                printf("\nOpção Inválida... Tentar Novamente?\n");
                pausar();
                break;
        }
    } while (opcao != 0);

    /* Para liberar memoria */
    free(usuarios);
    free(criptos);

    return 0;
}

/*COMPILAR: gcc main.c arquivos.c -o crypto_wallet */
/*EXECUTAR: ./crypto_wallet.exe */

/*ALUNOS: RAFAEL SOUZA RIBEIRO & MARCUS VINICIUS - ENGENHARIA DA COMPUTAÇÃO...*/