#ifndef ARQUIVOS_H
#define ARQUIVOS_H

typedef struct {
    int id;
    char nome[50];
    char simbolo[10];
    float precoAtual;
} Criptomoeda;

typedef struct {
    int idTransacao;
    int idCripto;
    float quantidade;
    float valorUSD;
    char tipo[10];
    char data[11];
} Transacao;

typedef struct {
    int id;
    char nome[50];
    char email[70];
    float saldoUSD;
    Transacao historico[100];
    int totalTransacoes;
} Usuario;

extern Usuario *usuarios;
extern int totalusuarios; 
extern int capacidadeUsuarios;

extern Criptomoeda *criptos;
extern int totalCriptos;
extern int capacidadeCriptos;

void salvarDadosBinario();
void carregarDadosBinario();
void gerarRelatorioTextual();

#endif