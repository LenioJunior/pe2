#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _CRT_SECURE_NO_WARNINGS

#define MAX_NOME 50
#define MAX_SERVICOS_ORDEM 5

typedef struct {
    int id;
    char nome[MAX_NOME];
    char raca[MAX_NOME];
    int idade;
} Pet;

typedef struct {
    int id;
    char descricao[MAX_NOME];
    float preco;
} Servico;

typedef struct {
    int id_ordem;
    Pet pet_cliente;
    Servico servicos_contratados[MAX_SERVICOS_ORDEM]; 
    float valor_total;
    int total_servicos;
} OrdemServico;

Servico servicos_disponiveis[] = {
    {1, "Banho Simples", 30.00},
    {2, "Tosa Higiênica", 25.00},
    {3, "Banho e Tosa Completa", 60.00},
    {4, "Hospedagem por Dia", 50.00},
    {5, "Consulta Veterinária", 80.00}
};
const int NUM_SERVICOS_DISPONIVEIS = sizeof(servicos_disponiveis) / sizeof(Servico);

Pet *lista_pets = NULL;
int num_pets = 0;
int capacidade_pets = 0;

OrdemServico *lista_ordens = NULL;
int num_ordens = 0;
int capacidade_ordens = 0;

Pet *buscar_pet_por_id(int id_alvo) {
    for (int i = 0; i < num_pets; i++) {
        Pet *p_atual = &lista_pets[i];
        if (p_atual->id == id_alvo) {
            return p_atual;
        }
    }
    return NULL;
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void liberar_tudo() {
  
    if (lista_pets != NULL) {
        free(lista_pets);
        lista_pets = NULL;
    }
    if (lista_ordens != NULL) {
        free(lista_ordens);
        lista_ordens = NULL;
    }
    num_pets = 0;
    capacidade_pets = 0;
    num_ordens = 0;
    capacidade_ordens = 0;
    printf("\nMemória liberada com sucesso. Sistema encerrado.\n");
}

void salvar_em_binario() {
    FILE *arq = fopen("dados.bin", "wb");
    if (arq == NULL) {
        perror("Erro ao abrir dados.bin para escrita binária");
        return;
    }
    
    fwrite(&num_pets, sizeof(int), 1, arq);
    if (num_pets > 0) {
        fwrite(lista_pets, sizeof(Pet), num_pets, arq);
    }
    
    fwrite(&num_ordens, sizeof(int), 1, arq);
    if (num_ordens > 0) {
        fwrite(lista_ordens, sizeof(OrdemServico), num_ordens, arq);
    }
    
    fclose(arq);
    printf("\nDados (%d Pets, %d Ordens) salvos em 'dados.bin' com sucesso.\n", num_pets, num_ordens);
}

void carregar_de_binario() {
    FILE *arq = fopen("dados.bin", "rb");
    if (arq == NULL) {
        printf("Arquivo 'dados.bin' não encontrado. Iniciando com dados vazios.\n");
        return;
    }
    
    fread(&num_pets, sizeof(int), 1, arq);
    if (num_pets > 0) {
        capacidade_pets = num_pets + 10;
        lista_pets = (Pet *)malloc(capacidade_pets * sizeof(Pet));
        fread(lista_pets, sizeof(Pet), num_pets, arq);
    }
    
    fread(&num_ordens, sizeof(int), 1, arq);
    if (num_ordens > 0) {
        capacidade_ordens = num_ordens + 10;
        lista_ordens = (OrdemServico *)malloc(capacidade_ordens * sizeof(OrdemServico));
        fread(lista_ordens, sizeof(OrdemServico), num_ordens, arq);
    }
    
    fclose(arq);
    printf("Dados carregados de 'dados.bin' (%d Pets, %d Ordens).\n", num_pets, num_ordens);
}

void gerar_relatorio_texto() {
    FILE *arq = fopen("relatorio.txt", "w");
    if (arq == NULL) {
        perror("Erro ao abrir relatorio.txt para escrita");
        return;
    }
    
    fprintf(arq, "=== RELATÓRIO DO SISTEMA BOLHINHAS DE SABÃO ===\n\n");
    
    // Relatório de Pets
    fprintf(arq, "--- 1. CADASTRO DE PETS (%d registros) ---\n", num_pets);
    for (int i = 0; i < num_pets; i++) {
        Pet *p_atual = &lista_pets[i];
        fprintf(arq, "ID: %d | Nome: %s | Raça: %s | Idade: %d anos\n", 
                p_atual->id, p_atual->nome, p_atual->raca, p_atual->idade);
    }
    fprintf(arq, "--------------------------------------------\n\n");

    fprintf(arq, "--- 2. ORDENS DE SERVIÇO (%d registros) ---\n", num_ordens);
    for (int i = 0; i < num_ordens; i++) {
        OrdemServico *o_atual = &lista_ordens[i];
        fprintf(arq, "ORDEM ID: %d | PET: %s (ID: %d)\n", 
                o_atual->id_ordem, o_atual->pet_cliente.nome, o_atual->pet_cliente.id);
        fprintf(arq, "  Serviços Contratados (%d):\n", o_atual->total_servicos);
        for (int j = 0; j < o_atual->total_servicos; j++) {
             fprintf(arq, "    - %s (Preço: R$ %.2f)\n", 
                    o_atual->servicos_contratados[j].descricao, 
                    o_atual->servicos_contratados[j].preco);
        }
        fprintf(arq, "  VALOR TOTAL DA ORDEM: R$ %.2f\n", o_atual->valor_total);
        fprintf(arq, "--------------------------------------------\n");
    }
    
    fclose(arq);
    printf("Relatório gerado em 'relatorio.txt' com sucesso.\n");
}

void realocar_memoria_pets() {
    capacidade_pets += 10;
    lista_pets = (Pet *)realloc(lista_pets, capacidade_pets * sizeof(Pet));
    if (lista_pets == NULL) {
        perror("Erro ao realocar memória para Pets");
        exit(EXIT_FAILURE);
    }
}

void adicionar_pet(Pet *novo_pet) {
    if (num_pets >= capacidade_pets) {
        realocar_memoria_pets();
    }
    
    lista_pets[num_pets] = *novo_pet; 
    
    Pet *p = &lista_pets[num_pets]; 
    p->id = num_pets + 1;
    
    num_pets++;
    printf("✅ Pet '%s' (ID: %d) adicionado com sucesso.\n", p->nome, p->id);
}

void listar_pets() {
    if (num_pets == 0) {
        printf("⚠️ Nenhum Pet cadastrado.\n");
        return;
    }
    
    printf("\n--- LISTA DE PETS (%d registros) ---\n", num_pets);
    for (int i = 0; i < num_pets; i++) {
        Pet *p_atual = &lista_pets[i]; // Acesso via ponteiro
        printf("ID: %d | Nome: %s | Raça: %s | Idade: %d\n", 
               p_atual->id, p_atual->nome, p_atual->raca, p_atual->idade);
    }
    printf("-----------------------------------------\n");
}

void atualizar_pet(int id_alvo) {
    Pet *p_encontrado = buscar_pet_por_id(id_alvo);

    if (p_encontrado == NULL) {
        printf("ERRO: Pet com ID %d não encontrado para atualização.\n", id_alvo);
        return;
    }

    printf("\nAtualizando Pet ID: %d (Nome atual: %s)\n", p_encontrado->id, p_encontrado->nome);

    printf("Novo Nome: ");
    limpar_buffer();
    scanf(" %49[^\n]", p_encontrado->nome); 
    
    printf("Nova Raça: ");
    limpar_buffer();
    scanf(" %49[^\n]", p_encontrado->raca);
    
    printf("Nova Idade (anos): ");
    scanf("%d", &p_encontrado->idade); 

    printf("✅ Pet %s (ID: %d) atualizado com sucesso.\n", p_encontrado->nome, p_encontrado->id);
}

void remover_pet(int id_alvo) {
    int indice_alvo = -1;
    
    for (int i = 0; i < num_pets; i++) {
        if (lista_pets[i].id == id_alvo) {
            indice_alvo = i;
            break;
        }
    }

    if (indice_alvo == -1) {
        printf("ERRO: Pet com ID %d não encontrado.\n", id_alvo);
        return;
    }
    
    for (int i = indice_alvo; i < num_pets - 1; i++) {
        lista_pets[i] = lista_pets[i+1]; 
    }
    
    num_pets--; 
    
    if (capacidade_pets - num_pets >= 10 && num_pets > 0) {
         capacidade_pets = num_pets;
         lista_pets = (Pet *)realloc(lista_pets, capacidade_pets * sizeof(Pet));
    } else if (num_pets == 0) {
         free(lista_pets);
         lista_pets = NULL;
         capacidade_pets = 0;
    }
    
    printf("✅ Pet (ID: %d) removido com sucesso.\n", id_alvo);
}

void buscar_pet(char *termo_busca) {
    int encontrado = 0;
    
    printf("\n--- RESULTADOS DA BUSCA por '%s' ---\n", termo_busca);

    for (int i = 0; i < num_pets; i++) {
        Pet *p_atual = &lista_pets[i];
        
        char nome_lower[MAX_NOME];
        strcpy(nome_lower, p_atual->nome);
        for(int k=0; nome_lower[k]; k++){
            nome_lower[k] = tolower(nome_lower[k]);
        }
        
        char termo_lower[MAX_NOME];
        strcpy(termo_lower, termo_busca);
        for(int k=0; termo_lower[k]; k++){
            termo_lower[k] = tolower(termo_lower[k]);
        }
        
        if (strstr(nome_lower, termo_lower) != NULL || 
            (atoi(termo_busca) > 0 && p_atual->id == atoi(termo_busca))) 
        {
            printf("ID: %d | Nome: %s | Raça: %s | Idade: %d\n", 
                   p_atual->id, p_atual->nome, p_atual->raca, p_atual->idade);
            encontrado++;
        }
    }
    
    if (encontrado == 0) {
        printf("Nenhum Pet encontrado com o termo '%s'.\n", termo_busca);
    }
    printf("-----------------------------------------\n");
}

void realocar_memoria_ordens() {
    capacidade_ordens += 10;
    lista_ordens = (OrdemServico *)realloc(lista_ordens, capacidade_ordens * sizeof(OrdemServico));
    if (lista_ordens == NULL) {
        perror("Erro ao realocar memória para Ordens de Serviço");
        exit(EXIT_FAILURE);
    }
}

void adicionar_ordem_servico() {
    int id_pet, id_servico, cont = 0;
    char continuar;
    float total = 0.0;
    
    if (num_pets == 0) {
        printf("ERRO: Cadastre Pets primeiro para criar uma Ordem de Serviço.\n");
        return;
    }
    
    printf("\nDigite o ID do Pet cliente para a Ordem de Serviço: ");
    if (scanf("%d", &id_pet) != 1) { limpar_buffer(); printf("ID inválido.\n"); return; }
    
    Pet *cliente = buscar_pet_por_id(id_pet);
    if (cliente == NULL) {
        printf("ERRO: Pet com ID %d não encontrado.\n", id_pet);
        return;
    }
    
    OrdemServico nova_ordem = {0};
    nova_ordem.pet_cliente = *cliente; 
    
    printf("\nCriando Ordem para o Pet: %s (ID: %d)\n", cliente->nome, cliente->id);
    
    do {
        if (cont >= MAX_SERVICOS_ORDEM) {
            printf("Limite máximo de %d serviços por ordem atingido.\n", MAX_SERVICOS_ORDEM);
            break;
        }

        printf("\n--- SERVIÇOS DISPONÍVEIS ---\n");
        for (int i = 0; i < NUM_SERVICOS_DISPONIVEIS; i++) {
            printf("%d. %-30s R$ %.2f\n", 
                   servicos_disponiveis[i].id, 
                   servicos_disponiveis[i].descricao, 
                   servicos_disponiveis[i].preco);
        }
        printf("---------------------------\n");
        
        printf("Digite o ID do Serviço a ser adicionado: ");
        if (scanf("%d", &id_servico) != 1) { limpar_buffer(); printf("ID inválido.\n"); break; }
        
        // Busca o serviço na lista estática
        Servico *servico_selecionado = NULL;
        for (int i = 0; i < NUM_SERVICOS_DISPONIVEIS; i++) {
            if (servicos_disponiveis[i].id == id_servico) {
                servico_selecionado = &servicos_disponiveis[i];
                break;
            }
        }
        
        if (servico_selecionado != NULL) {
            nova_ordem.servicos_contratados[cont] = *servico_selecionado; 
            total += servico_selecionado->preco;
            cont++;
            printf("✅ Serviço '%s' adicionado. Total parcial: R$ %.2f\n", servico_selecionado->descricao, total);
        } else {
            printf("ERRO: Serviço ID %d não encontrado.\n", id_servico);
        }
        
        limpar_buffer();
        printf("Adicionar outro serviço? (S/N): ");
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while (continuar == 'S');
    
    if (cont == 0) {
        printf("Ordem de Serviço cancelada (nenhum serviço adicionado).\n");
        return;
    }
    
    if (num_ordens >= capacidade_ordens) {
        realocar_memoria_ordens();
    }
    
    nova_ordem.total_servicos = cont;
    nova_ordem.valor_total = total;
    
    lista_ordens[num_ordens] = nova_ordem;
    lista_ordens[num_ordens].id_ordem = num_ordens + 1;
    
    num_ordens++;
    printf("\n✅ Ordem de Serviço (ID: %d) criada. Valor Final: R$ %.2f\n", 
           lista_ordens[num_ordens-1].id_ordem, total);
}

void listar_ordens_servico() {
    if (num_ordens == 0) {
        printf("⚠️ Nenhuma Ordem de Serviço cadastrada.\n");
        return;
    }
    
    printf("\n--- LISTA DE ORDENS DE SERVIÇO (%d registros) ---\n", num_ordens);
    for (int i = 0; i < num_ordens; i++) {
        OrdemServico *o_atual = &lista_ordens[i]; // Uso de ponteiro
        
        printf("ID Ordem: %d | Pet: %s (ID: %d) | Total Serviços: %d\n", 
               o_atual->id_ordem, o_atual->pet_cliente.nome, o_atual->pet_cliente.id, o_atual->total_servicos);
        
        printf("  Serviços:\n");
        for (int j = 0; j < o_atual->total_servicos; j++) {
            Servico *s_contratado = &o_atual->servicos_contratados[j];
            printf("    - %s (R$ %.2f)\n", s_contratado->descricao, s_contratado->preco);
        }
        printf("  VALOR TOTAL: R$ %.2f\n", o_atual->valor_total);
        printf("---------------------------------------------------\n");
    }
}

void menu_gerenciar_pets() {
    int opcao, id_busca;
    char termo[MAX_NOME];
    
    do {
        printf("\n--- MENU GESTÃO DE PETS (Clientes) ---\n");
        printf("1. Adicionar Novo Pet\n");
        printf("2. Listar Todos os Pets\n");
        printf("3. Buscar Pet (ID/Nome)\n");
        printf("4. Atualizar Pet (por ID)\n");
        printf("5. Remover Pet (por ID)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opção: ");
        if (scanf("%d", &opcao) != 1) { limpar_buffer(); opcao = -1; }

        switch (opcao) {
            case 1: { 
                Pet novo = {0}; 
                limpar_buffer();
                printf("Nome do Pet: ");
                scanf(" %49[^\n]", novo.nome);
                printf("Raça do Pet: ");
                scanf(" %49[^\n]", novo.raca);
                printf("Idade (anos): ");
                scanf("%d", &novo.idade);
                adicionar_pet(&novo); 
                break;
            }
            case 2: listar_pets(); break;
            case 3:
                limpar_buffer();
                printf("Digite o ID ou parte do Nome para buscar: ");
                scanf(" %49[^\n]", termo);
                buscar_pet(termo);
                break;
            case 4:
                printf("Digite o ID do Pet a atualizar: ");
                scanf("%d", &id_busca);
                atualizar_pet(id_busca);
                break;
            case 5:
                printf("Digite o ID do Pet a remover: ");
                scanf("%d", &id_busca);
                remover_pet(id_busca);
                break;
            case 0: break;
            default: printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void menu_principal() {
    printf("\n==== SISTEMA BOLHINHAS DE SABÃO ====\n");
    printf("1. Gerenciar Pets (Clientes)\n");
    printf("2. Criar Ordem de Serviço\n");
    printf("3. Listar Ordens de Serviço\n");
    printf("4. Salvar Dados (Binário)\n");
    printf("5. Gerar Relatório (Texto)\n");
    printf("0. Sair e Liberar Memória\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;
    
    carregar_de_binario(); 

    do {
        menu_principal();
        if (scanf("%d", &opcao) != 1) { limpar_buffer(); opcao = -1; }

        switch (opcao) {
            case 1: menu_gerenciar_pets(); break;
            case 2: adicionar_ordem_servico(); break;
            case 3: listar_ordens_servico(); break;
            case 4: salvar_em_binario(); break;
            case 5: gerar_relatorio_texto(); break;
            case 0: break; 
            default: printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberar_tudo(); 
    
    return 0;
}

