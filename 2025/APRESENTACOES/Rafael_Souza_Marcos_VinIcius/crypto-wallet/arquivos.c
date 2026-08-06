#include "arquivos.h"
#include <stdio.h>
#include <stdlib.h>

void salvarDadosBinario() {  /* Escreve counters e vet de structs com fwrite, usa ponteiro pra acessar. */
    FILE *file = fopen("dados.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir dados.bin para salvar\n");
        return;
    }

    /* Salva as cryptos */
    fwrite(&totalCriptos, sizeof(int), 1, file);  
    fwrite(criptos, sizeof(Criptomoeda), totalCriptos, file);

    /* Salva os usuarios */
    fwrite(&totalusuarios, sizeof(int), 1, file);
    for (int i = 0; i < totalusuarios; i++) {
        Usuario *u = &usuarios[i];  /* Um ponteiro que salva struct */
        fwrite(u, sizeof(Usuario), 1, file);  /* Salva toda struct, incluindo vetor de transações */
    }

    fclose(file);
    printf("Dados Salvos em dados.bin com Sucesso!\n");
}

void carregarDadosBinario() {  /* Realloc memoria, le structs inteiras com fread */
    FILE *file = fopen("dados.bin", "rb");
    if (file == NULL) {
        printf("Arquivo dados.bin não Encontrado, começando vazio.\n");
        return;
    }

    /* Carrega as cryptos */
    fread(&totalCriptos, sizeof(int), 1, file);
    capacidadeCriptos = totalCriptos;
    criptos = (Criptomoeda*) realloc(criptos, capacidadeCriptos * sizeof(Criptomoeda));
    fread(criptos, sizeof(Criptomoeda), totalCriptos, file);

    /* Carregar usuarios */
    fread(&totalusuarios, sizeof(int), 1, file);
    capacidadeUsuarios = totalusuarios;
    usuarios = (Usuario*) realloc(usuarios, capacidadeUsuarios * sizeof(Usuario));
    for (int i = 0; i < totalusuarios; i++) {
        fread(&usuarios[i], sizeof(Usuario), 1, file);
    }
    fclose(file);
    printf("Dados carregados de dados.bin com sucesso!\n");
}

void gerarRelatorioTextual() {  /* Printar tudo em formato legível, com loops e ponteiros pra acessar dados. */
    FILE *file = fopen("relatorio.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir relatorio.txt!\n");
        return;
    }

    fprintf(file, "==== RELATÓRIO DE CARTEIRAS DE CRIPTOMOEDAS ====\n\n");

    for (int i = 0; i < totalusuarios; i++) {
        Usuario *u = &usuarios[i];
        fprintf(file, "Usuário ID: %d - Nome: %s - E-mail: %s\n", u->id, u->nome, u->email);  /*  add u->id e ordem certa */
        fprintf(file, "Saldo USD: %.2f\n", u->saldoUSD);
        fprintf(file, "Transações: %d\n", u->totalTransacoes);
        fprintf(file, "Histórico:\n");

        for (int j = 0; j < u->totalTransacoes; j++) {
            Transacao *t = &u->historico[j];
            Criptomoeda *c = NULL;
            for (int k = 0; k < totalCriptos; k++) {
                if (criptos[k].id == t->idCripto) {
                    c = &criptos[k];
                    break;
                }
            }
            if (c != NULL) {  /* Add != NULL pra segurança */
                fprintf(file, "%s - %s: %.2f %s por %.2f USD (%s)\n", t->data, t->tipo, t->quantidade, c->simbolo, t->valorUSD, c->nome);
            }
        }
        fprintf(file, "-----------------------------------------\n\n");
    }
    fclose(file);
    printf("Relatório gerado em relatorio.txt com Sucesso!\n");
}