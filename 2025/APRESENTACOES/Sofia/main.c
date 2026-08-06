#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_ROUPAS 20


// =========================================================
//                      STRUCTS
// =========================================================


// CLIENTE
typedef struct {
   int id;
   char nome[MAX_NOME];
   char telefone[20];
   char email[MAX_EMAIL];
} Cliente;


// ROUPA
typedef struct {
   int id;
   char nome[MAX_NOME];
   char tamanho[5];
   float preco;
} Roupa;


// VENDA
typedef struct {
   int idVenda;
   Cliente cliente;
   Roupa roupas[MAX_ROUPAS];
   int qtdRoupas;
   float valorTotal;
} Venda;


// =========================================================
//     VARIÁVEIS GLOBAIS
// =========================================================
Cliente *clientes = NULL;
Roupa *roupas = NULL;
Venda *vendas = NULL;


int qtdClientes = 0;
int qtdRoupas = 0;
int qtdVendas = 0;


int ultimoIDC = 1, ultimoIDR = 1, ultimoIDV = 1;


// =========================================================
//        FUNÇÃO PARA GERAR IDs AUTOMÁTICOS
// =========================================================
int gerarID(int tipo) {
   if (tipo == 1) return ultimoIDC++;
   if (tipo == 2) return ultimoIDR++;
   return ultimoIDV++;
}


// =========================================================
//                 CRUD DE CLIENTES
// =========================================================
void adicionarCliente() {
   clientes = realloc(clientes, (qtdClientes + 1) * sizeof(Cliente));


   clientes[qtdClientes].id = gerarID(1);


   printf("Nome completo do cliente: ");
   scanf(" %[^\n]", clientes[qtdClientes].nome);


   printf("Telefone: ");
   scanf(" %[^\n]", clientes[qtdClientes].telefone);


   printf("Email: ");
   scanf(" %[^\n]", clientes[qtdClientes].email);


   qtdClientes++;
   printf("Cliente cadastrado!\n");
}


void listarClientes() {
   printf("\n--- CLIENTES ---\n");
   for (int i = 0; i < qtdClientes; i++) {
       printf("ID: %d | Nome: %s | Tel: %s | Email: %s\n",
              clientes[i].id, clientes[i].nome, clientes[i].telefone, clientes[i].email);
   }
}


Cliente *buscarCliente(int id) {
   for (int i = 0; i < qtdClientes; i++)
       if (clientes[i].id == id)
           return &clientes[i];
   return NULL;
}


void editarCliente() {
   int id;
   printf("ID do cliente para editar: ");
   scanf("%d", &id);


   Cliente *c = buscarCliente(id);
   if (!c) {
       printf("Cliente não encontrado!\n");
       return;
   }


   printf("Novo nome completo: ");
   scanf(" %[^\n]", c->nome);


   printf("Novo telefone: ");
   scanf(" %[^\n]", c->telefone);


   printf("Novo email: ");
   scanf(" %[^\n]", c->email);


   printf("Cliente editado!\n");
}


void excluirCliente() {
   int id;
   printf("ID do cliente para excluir: ");
   scanf("%d", &id);


   int pos = -1;
   for (int i = 0; i < qtdClientes; i++)
       if (clientes[i].id == id)
           pos = i;


   if (pos == -1) {
       printf("Cliente não encontrado!\n");
       return;
   }


   for (int i = pos; i < qtdClientes - 1; i++)
       clientes[i] = clientes[i + 1];


   qtdClientes--;
   clientes = realloc(clientes, qtdClientes * sizeof(Cliente));


   printf("Cliente excluído!\n");
}


// =========================================================
//                 CRUD DE ROUPAS
// =========================================================
void adicionarRoupa() {
   roupas = realloc(roupas, (qtdRoupas + 1) * sizeof(Roupa));


   roupas[qtdRoupas].id = gerarID(2);


   printf("Nome da roupa: ");
   scanf(" %[^\n]", roupas[qtdRoupas].nome);


   printf("Tamanho (P/M/G): ");
   scanf(" %[^\n]", roupas[qtdRoupas].tamanho);


   printf("Preço: ");
   scanf("%f", &roupas[qtdRoupas].preco);


   qtdRoupas++;
   printf("Roupa cadastrada!\n");
   getchar();
}


void listarRoupas() {
   printf("\n--- ESTOQUE ---\n");
   for (int i = 0; i < qtdRoupas; i++) {
       printf("ID: %d | %s | Tam: %s | R$ %.2f\n",
              roupas[i].id, roupas[i].nome, roupas[i].tamanho, roupas[i].preco);
   }
}


Roupa *buscarRoupa(int id) {
   for (int i = 0; i < qtdRoupas; i++)
       if (roupas[i].id == id)
           return &roupas[i];
   return NULL;
}


void editarRoupa() {
   int id;
   printf("ID da roupa para editar: ");
   scanf("%d", &id);


   Roupa *r = buscarRoupa(id);
   if (!r) {
       printf("Roupa não encontrada!\n");
       return;
   }


   printf("Novo nome: ");
   scanf(" %[^\n]", r->nome);


   printf("Novo tamanho: ");
   scanf(" %[^\n]", r->tamanho);


   printf("Novo preço: ");
   scanf("%f", &r->preco);


   printf("Roupa editada!\n");
}


void excluirRoupa() {
   int id;
   printf("ID da roupa para excluir: ");
   scanf("%d", &id);


   int pos = -1;
   for (int i = 0; i < qtdRoupas; i++)
       if (roupas[i].id == id)
           pos = i;


   if (pos == -1) {
       printf("Roupa não encontrada!\n");
       return;
   }


   for (int i = pos; i < qtdRoupas - 1; i++)
       roupas[i] = roupas[i + 1];


   qtdRoupas--;
   roupas = realloc(roupas, qtdRoupas * sizeof(Roupa));


   printf("Roupa excluída!\n");
}


// =========================================================
//                REGISTRAR VENDA
// =========================================================
void registrarVenda() {
   if (qtdClientes == 0 || qtdRoupas == 0) {
       printf("Cadastre clientes e roupas antes!\n");
       return;
   }


   vendas = realloc(vendas, (qtdVendas + 1) * sizeof(Venda));
   Venda *v = &vendas[qtdVendas];


   v->idVenda = gerarID(3);
   v->valorTotal = 0;


   int idCliente;
   printf("ID do cliente: ");
   scanf("%d", &idCliente);


   Cliente *c = buscarCliente(idCliente);
   if (!c) {
       printf("Cliente não encontrado!\n");
       return;
   }


   v->cliente = *c;


   printf("Quantas peças deseja comprar (max %d)? ", MAX_ROUPAS);
   scanf("%d", &v->qtdRoupas);


   for (int i = 0; i < v->qtdRoupas; i++) {
       int idRoupa;
       printf("ID da roupa %d: ", i + 1);
       scanf("%d", &idRoupa);


       Roupa *r = buscarRoupa(idRoupa);
       if (!r) {
           printf("Roupa não encontrada!\n");
           i--;
       } else {
           v->roupas[i] = *r;
           v->valorTotal += r->preco;
       }
   }


   qtdVendas++;
   printf("Venda registrada! Total: R$ %.2f\n", v->valorTotal);
}
void listarVendas() {
   printf("\n--- VENDAS ---\n");


   for (int i = 0; i < qtdVendas; i++) {
       Venda *v = &vendas[i];


       printf("\nVenda ID: %d\nCliente: %s\nTotal: R$ %.2f\nRoupas:\n",
              v->idVenda, v->cliente.nome, v->valorTotal);


       for (int j = 0; j < v->qtdRoupas; j++) {
           printf("  - %s (Tam %s) - R$ %.2f\n",
                  v->roupas[j].nome,
                  v->roupas[j].tamanho,
                  v->roupas[j].preco);
       }
   }
}


// =========================================================
//                RELATÓRIO (TELA + ARQUIVO)
// =========================================================
void gerarRelatorio() {
   FILE *f = fopen("relatorio.txt", "w");
   if (!f) return;


   printf("\n======== RELATÓRIO ========\n");
   fprintf(f, "======== RELATÓRIO ========\n");


   printf("\n--- CLIENTES ---\n");
   fprintf(f, "\n--- CLIENTES ---\n");
   for (int i = 0; i < qtdClientes; i++) {
       printf("%d - %s (%s) Email: %s\n", clientes[i].id, clientes[i].nome, clientes[i].telefone, clientes[i].email);
       fprintf(f, "%d - %s (%s) Email: %s\n", clientes[i].id, clientes[i].nome, clientes[i].telefone, clientes[i].email);
   }


   printf("\n--- ESTOQUE ---\n");
   fprintf(f, "\n--- ESTOQUE ---\n");
   for (int i = 0; i < qtdRoupas; i++) {
       printf("%d - %s (Tam %s) R$ %.2f\n", roupas[i].id, roupas[i].nome, roupas[i].tamanho, roupas[i].preco);
       fprintf(f, "%d - %s (Tam %s) R$ %.2f\n", roupas[i].id, roupas[i].nome, roupas[i].tamanho, roupas[i].preco);
   }


   printf("\n--- VENDAS ---\n");
   fprintf(f, "\n--- VENDAS ---\n");
   for (int i = 0; i < qtdVendas; i++) {
       Venda *v = &vendas[i];


       printf("\nVenda %d\nCliente: %s\nTotal: R$ %.2f\n",
              v->idVenda, v->cliente.nome, v->valorTotal);


       fprintf(f, "\nVenda %d\nCliente: %s\nTotal: R$ %.2f\n",
               v->idVenda, v->cliente.nome, v->valorTotal);


       for (int j = 0; j < v->qtdRoupas; j++) {
           printf("  - %s (Tam %s) R$ %.2f\n",
                  v->roupas[j].nome, v->roupas[j].tamanho, v->roupas[j].preco);


           fprintf(f, "  - %s (Tam %s) R$ %.2f\n",
                   v->roupas[j].nome, v->roupas[j].tamanho, v->roupas[j].preco);
       }
   }


   fclose(f);
   printf("\nRelatório salvo como 'relatorio.txt'!\n");
}


// =========================================================
//     SALVAR E CARREGAR ARQUIVO BINÁRIO
// =========================================================
void salvarBinario() {
   FILE *f = fopen("dados.bin", "wb");
   if (!f) return;


   fwrite(&qtdClientes, sizeof(int), 1, f);
   fwrite(clientes, sizeof(Cliente), qtdClientes, f);


   fwrite(&qtdRoupas, sizeof(int), 1, f);
   fwrite(roupas, sizeof(Roupa), qtdRoupas, f);


   fwrite(&qtdVendas, sizeof(int), 1, f);
   fwrite(vendas, sizeof(Venda), qtdVendas, f);


   fwrite(&ultimoIDC, sizeof(int), 1, f);
   fwrite(&ultimoIDR, sizeof(int), 1, f);
   fwrite(&ultimoIDV, sizeof(int), 1, f);


   fclose(f);
   printf("Dados salvos!\n");
}


void carregarBinario() {
   FILE *f = fopen("dados.bin", "rb");
   if (!f) return;


   fread(&qtdClientes, sizeof(int), 1, f);
   clientes = malloc(qtdClientes * sizeof(Cliente));
   fread(clientes, sizeof(Cliente), qtdClientes, f);


   fread(&qtdRoupas, sizeof(int), 1, f);
   roupas = malloc(qtdRoupas * sizeof(Roupa));
   fread(roupas, sizeof(Roupa), qtdRoupas, f);


   fread(&qtdVendas, sizeof(int), 1, f);
   vendas = malloc(qtdVendas * sizeof(Venda));
   fread(vendas, sizeof(Venda), qtdVendas, f);


   fread(&ultimoIDC, sizeof(int), 1, f);
   fread(&ultimoIDR, sizeof(int), 1, f);
   fread(&ultimoIDV, sizeof(int), 1, f);


   fclose(f);
   printf("Dados carregados!\n");
}


// =========================================================
//                        MENU
// =========================================================
int main() {
   carregarBinario();


   int op;


   do {
       printf("\n====== MENU LOJA DE ROUPAS ======\n");
       printf("1 - Cadastrar cliente\n");
       printf("2 - Cadastrar roupa\n");
       printf("3 - Registrar venda\n");
       printf("4 - Listar clientes\n");
       printf("5 - Listar roupas\n");
       printf("6 - Listar vendas\n");
       printf("7 - Salvar dados\n");
       printf("8 - Gerar relatório\n");
       printf("9 - Editar cliente\n");
       printf("10 - Excluir cliente\n");
       printf("11 - Editar roupa\n");
       printf("12 - Excluir roupa\n");
       printf("0 - Sair\nEscolha: ");
       scanf("%d", &op);


       switch (op) {
       case 1: adicionarCliente(); break;
       case 2: adicionarRoupa(); break;
       case 3: registrarVenda(); break;
       case 4: listarClientes(); break;
       case 5: listarRoupas(); break;
       case 6: listarVendas(); break;
       case 7: salvarBinario(); break;
       case 8: gerarRelatorio(); break;
       case 9: editarCliente(); break;
       case 10: excluirCliente(); break;
       case 11: editarRoupa(); break;
       case 12: excluirRoupa(); break;
       }
   } while (op != 0);


   salvarBinario();
   return 0;
}



