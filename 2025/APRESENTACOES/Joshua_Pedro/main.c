#include <stdio.h>
#include <stdlib.h>

#define limpa while(getchar()!='\n');
#define apaga system("cls||clear");

//======================================================== STRUCTS ========================================================
typedef struct{
    int nummesa;
    int andarmesa;
}mesa_;

typedef struct{
    int numpedido, qtdpedido;
}pedido_;

typedef struct{
    mesa_ mesa;
    pedido_ pedido[20];
    int idcomanda, flagcomanda;
    float precocomanda;
}comanda_;

//======================================================== VARIAVEIS GLOBAIS ========================================================
comanda_ *comanda = NULL;
int quantidadecomanda = 0, *totalpedidos = NULL, geraid, maiorid, comandascadastradas = 0, comandasremovidas = 0;

//======================================================== PROTOTIPO FUNCOES ========================================================
void criacomanda();
void menu();
void listarcomanda();
void removecomanda();
void checavetornull();
void cardapio();
void digitanomepedido(int numpedido, int qtd);
void buscacomanda();
void atualizacomanda();
void calculaprecocomanda(int numpedido, int c, int qtd);
void salvaarquivo();
void carregaarquivo();
void corrigeid();
void gerarelatorio();
void digitanomepedidorelatorio(FILE *relatorio, int numpedido, int qtd);

//======================================================== INT MAIN ========================================================
int main()
{
    carregaarquivo();
    corrigeid();
    menu();
    salvaarquivo();
    gerarelatorio();
    free(comanda);
    free(totalpedidos);
    return 0;
}

//======================================================== FUNCOES ========================================================
void checavetornull()
{
    if(((comanda = realloc(comanda, (quantidadecomanda)*sizeof(comanda_))) == NULL))
    {
        printf("Erro ao realocar memoria!\n");
        exit(1);
    }
    if(((totalpedidos = realloc(totalpedidos, (quantidadecomanda)*sizeof(int))) == NULL))
    {
        printf("Erro ao realocar memoria!\n");
        exit(1);
    }
}

void gerarelatorio()
{
    int i, d;
    FILE *relatorio = fopen("relatorio.txt", "w");
    if(relatorio == NULL)
    {
        printf("Nao foi possivel gerar o relatorio!\n");
        exit(1);
    }
    fprintf(relatorio, "Comandas adicionadas: %d\n", comandascadastradas);
    fprintf(relatorio, "Comandas removidas: %d\n\n", comandasremovidas);
    if(comandascadastradas > 0)
        fprintf(relatorio, "================ Comandas Adicionadas ================\n\n");
    for(i = 0; i < quantidadecomanda; i++)
    {
        if(comanda[i].idcomanda > maiorid)
        {
            fprintf(relatorio, "Id: %d\nNumero da Mesa: %d\nAndar da Mesa: %d\n", (comanda[i]).idcomanda, (comanda[i]).mesa.nummesa, (comanda[i]).mesa.andarmesa);
            for(d = 0; d < totalpedidos[i]; d++)
            {
                fprintf(relatorio, "Pedido N%d: ", d+1);
                digitanomepedidorelatorio(relatorio, comanda[i].pedido[d].numpedido, comanda[i].pedido[d].qtdpedido);
                fprintf(relatorio, " x%d\n", (comanda[i]).pedido[d].qtdpedido);
                if(d == totalpedidos[i]-1)
                    fprintf(relatorio, "Valor da Comanda: R$%.2f\n", comanda[i].precocomanda);
            }
            fprintf(relatorio, "\n\n");
        }
    }
    if(comandasremovidas > 0)
        fprintf(relatorio, "================ Comandas Removidas ================\n\n");
    for(i = 0; i < quantidadecomanda; i++)
    {
        if(comanda[i].flagcomanda == 0)
        {
            fprintf(relatorio, "Id: %d\nNumero da Mesa: %d\nAndar da Mesa: %d\n", (comanda[i]).idcomanda, (comanda[i]).mesa.nummesa, (comanda[i]).mesa.andarmesa);
            for(d = 0; d < totalpedidos[i]; d++)
            {
                fprintf(relatorio, "Pedido N%d: ", d+1);
                digitanomepedidorelatorio(relatorio, comanda[i].pedido[d].numpedido, comanda[i].pedido[d].qtdpedido);
                fprintf(relatorio, " x%d\n", (comanda[i]).pedido[d].qtdpedido);
                if((comanda[i]).flagcomanda==1 && d == totalpedidos[i]-1)
                    fprintf(relatorio, "Valor da Comanda: R$%.2f\n", comanda[i].precocomanda);
            }
            fprintf(relatorio, "\n\n");
        }
    }
    fclose(relatorio);
}

void carregaarquivo()
{
    FILE *arq = fopen("comanda.bin", "rb");
    if(arq == NULL)
    {
        geraid = 1;
        return;
    }
    int contagem = 0;
    fread(&contagem, sizeof(int), 1, arq);
    quantidadecomanda = contagem;
    checavetornull();
    for (int i = 0; i < contagem; i++)
    {
        fread(&comanda[i], sizeof(comanda_), 1, arq);
        fread(&totalpedidos[i], sizeof(int), 1, arq);
        fread(comanda[i].pedido, sizeof(pedido_), totalpedidos[i], arq);
    }
    fclose(arq);
}

void corrigeid()
{
    int i;
    if(geraid != 1 && quantidadecomanda >= 1)
        geraid = comanda[quantidadecomanda-1].idcomanda + 1;
    else
        geraid = 1;
    maiorid = 0;
    for(i = 0; i < quantidadecomanda; i++)
    {
        if(comanda[i].idcomanda > maiorid)
            maiorid = comanda[i].idcomanda;
    }
}

void salvaarquivo()
{
    FILE *arq = fopen("comanda.bin", "wb");
    if(arq == NULL)
    {
        printf("Erro ao salvar arquivo!\n");
        exit(1);
    }
    int contagem = 0;
    for (int i = 0; i < quantidadecomanda; i++)
    {
        if (comanda[i].flagcomanda == 1)
            contagem++;
    }
    fwrite(&contagem, sizeof(int), 1, arq);
    for (int i = 0; i < quantidadecomanda; i++)
    {
        if (comanda[i].flagcomanda == 1)
        {
            fwrite(&comanda[i], sizeof(comanda_), 1, arq);
            fwrite(&totalpedidos[i], sizeof(int), 1, arq);
            fwrite(comanda[i].pedido, sizeof(pedido_), totalpedidos[i], arq);
        }
    }
    fclose(arq);
}

void menu()
{
    apaga
    int func;
    do{
        printf("============== MENU DE FUNCOES ==============\n  1) Criar uma nova comanda.\n  2) Remover uma comanda.\n  3) Atualizar uma comanda.\n  4) Listar comandas.\n  5) Buscar comanda.\n  0) Finalizar programa.\n=============================================\n\n");
        scanf("%d", &func);
        limpa
        switch(func)
        {
            case 1:
                apaga
                criacomanda();
                apaga
                break;
            case 2:
                apaga
                removecomanda();
                apaga
                break;
            case 3:
                apaga
                atualizacomanda();
                apaga
                break;
            case 4:
                apaga
                listarcomanda();
                apaga
                break;
            case 5:
                apaga
                buscacomanda();
                apaga
                break;
            default:
                apaga
                break;
        }
    }while(func!=0);
}

void cardapio()
{
    printf("============== CARDAPIO ==============\n  1) Bife a Parmegiana - R$39,99\n  2) Estrogonofe de Frango - R$39,99\n  3) Macarrao Molho Pomodoro - R$24,99\n  4) Salada - R$14,99\n  5) Torta Limao - R$19,99\n  6) Coca-Cola 2 Litros - R$ 11,99\n======================================\n\n");
}

void calculaprecocomanda(int numpedido, int c, int qtd)
{
    switch(numpedido)
    {
        case 1:
        case 2:
            comanda[c].precocomanda+=(39.99*qtd);
            break;
        case 3:
            comanda[c].precocomanda+=(24.99*qtd);
            break;
        case 4:
            comanda[c].precocomanda+=(14.99*qtd);
            break;
        case 5:
            comanda[c].precocomanda+=(19.99*qtd);
            break;
        case 6:
            comanda[c].precocomanda+=(11.99*qtd);
            break;
    }
}

void digitanomepedido(int numpedido, int qtd)
{
    switch(numpedido)
    {
        case 1:
            printf("Bife a Parmegiana");
            break;
        case 2:
            printf("Estrogonofe de Frango");
            break;
        case 3:
            printf("Macarrao Molho Pomodoro");
            break;
        case 4:
            printf("Salada");
            break;
        case 5:
            printf("Torta Limao");
            break;
        case 6:
            printf("Coca-Cola 2 Litros");
            break;
    }
}

void digitanomepedidorelatorio(FILE *relatorio, int numpedido, int qtd)
{
    switch(numpedido)
    {
        case 1:
            fprintf(relatorio, "Bife a Parmegiana");
            break;
        case 2:
            fprintf(relatorio, "Estrogonofe de Frango");
            break;
        case 3:
            fprintf(relatorio, "Macarrao Molho Pomodoro");
            break;
        case 4:
            fprintf(relatorio, "Salada");
            break;
        case 5:
            fprintf(relatorio, "Torta Limao");
            break;
        case 6:
            fprintf(relatorio, "Coca-Cola 2 Litros");
            break;
    }
}

void criacomanda()
{
    quantidadecomanda++;
    checavetornull();
    int indice = quantidadecomanda-1;
    totalpedidos[indice] = 0;
    comanda[indice].precocomanda = 0;
    comanda[indice].idcomanda = geraid;
    geraid++;
    printf("Digite o numero da mesa (digite -1 para cancelar a criacao de comanda): ");
    scanf("%d", &(comanda[indice]).mesa.nummesa);
    if((comanda[indice]).mesa.nummesa!=-1)
    {
        comanda[indice].flagcomanda = 1;
        printf("Digite o andar da mesa: ");
        scanf("%d", &(comanda[indice]).mesa.andarmesa);
        int i = 0;
        int numloop = 0;
        do{
            printf("\n");
            if(numloop==0)
                cardapio();
            printf("\nDigite o numero do pedido (digite -1 para encerrar o pedido): ");
            scanf("%d", &(comanda[indice]).pedido[i].numpedido);
            if(((comanda[indice]).pedido[i].numpedido < 1 || (comanda[indice]).pedido[i].numpedido > 6) && (comanda[indice]).pedido[i].numpedido != -1)
            {
                printf("Esse numero nao esta no cardapio!\n");
            }
            else
            {
                if((comanda[indice]).pedido[i].numpedido==-1)
                    i=-1;
                else
                {   
                    totalpedidos[indice]++;
                    printf("Digite a quantidade desse pedido: ");
                    scanf("%d", &(comanda[indice]).pedido[i].qtdpedido);
                    calculaprecocomanda((comanda[indice]).pedido[i].numpedido, indice, (comanda[indice]).pedido[i].qtdpedido);
                    if(i<19)
                        i++;
                    else
                    {
                        printf("Comanda cheia!\n");
                        i=-1;
                        limpa
                        printf("\nDigite enter para continuar.\n");
                        getchar();
                    }
                }
            }
            numloop++;
        }while(i!=-1);
        comandascadastradas++;
    }
    else
    {
        quantidadecomanda--;
        checavetornull();
    }
}

void removecomanda()
{
    int idapagar, c;
    printf("Digite o ID da comanda que voce quer apagar (digite -1 para cancelar).\n");
    scanf("%d", &idapagar);
    if(idapagar!=-1)
    {
        for(c = 0; c < quantidadecomanda; c++)
        {
            if((comanda[c]).idcomanda == idapagar && (comanda[c]).flagcomanda == 1)
            {
                comanda[c].flagcomanda = 0;
                printf("Comanda apagada com sucesso!\n");
                break;
            }
            else if(((comanda[c]).idcomanda == idapagar && (comanda[c]).flagcomanda == 0) || c == quantidadecomanda-1)
            {
                printf("Comanda nao encontrada.\n");
                break;
            }
        }
        limpa
        printf("\nDigite enter para continuar.\n");
        getchar();
        comandasremovidas++;
    }
}

void listarcomanda()
{
    int c, d;
    for(c = 0; c < quantidadecomanda; c++)
    {
        if((comanda[c]).flagcomanda==1)
        {
            printf("Id: %d\nNumero da Mesa: %d\nAndar da Mesa: %d\n", (comanda[c]).idcomanda, (comanda[c]).mesa.nummesa, (comanda[c]).mesa.andarmesa);
            for(d = 0; d < totalpedidos[c]; d++)
            {
                printf("Pedido N%d: ", d+1);
                digitanomepedido(comanda[c].pedido[d].numpedido, comanda[c].pedido[d].qtdpedido);
                printf(" x%d\n", (comanda[c]).pedido[d].qtdpedido);
                if(d == totalpedidos[c]-1)
                    printf("Valor da Comanda: R$%.2f\n", comanda[c].precocomanda);
            }
        printf("\n\n");
        }
    }
    printf("Digite enter para continuar.\n");
    getchar();
}

void buscacomanda()
{
    int c, d, idachar;
    printf("Digite o ID da comanda que voce quer ver (digite -1 para cancelar).\n");
    scanf("%d", &idachar);
    if(idachar!=-1)
    {
        for(c = 0; c < quantidadecomanda; c++)
        {
            if((comanda[c]).idcomanda == idachar && (comanda[c]).flagcomanda == 1)
            {
                {
                printf("Id: %d\nNumero da Mesa: %d\nAndar da Mesa: %d\n", (comanda[c]).idcomanda, (comanda[c]).mesa.nummesa, (comanda[c]).mesa.andarmesa);
                for(d = 0; d < totalpedidos[c]; d++)
                {
                    printf("Pedido N%d: ", d+1);
                    digitanomepedido(comanda[c].pedido[d].numpedido, comanda[c].pedido[d].qtdpedido);
                    printf(" x%d\n", (comanda[c]).pedido[d].qtdpedido);
                    if(d == totalpedidos[c]-1)
                        printf("Valor da Comanda: R$%.2f\n", comanda[c].precocomanda);
                }
                printf("\n\n");
                }
                break;
            }
            else if(c == quantidadecomanda-1)
                printf("Comanda nao encontrada.\n");
        }
        limpa
        printf("\nDigite enter para continuar.\n");
        getchar();
    }
}

void atualizacomanda()
{
    int c, d, idatualizar;
    printf("Digite o ID da comanda que voce quer atualizar (digite -1 para cancelar).\n");
    scanf("%d", &idatualizar);
    if(idatualizar!=-1)
    {
        for(c = 0; c < quantidadecomanda; c++)
        {
            if((comanda[c]).idcomanda == idatualizar && (comanda[c]).flagcomanda == 1)
            {
                printf("Digite o numero da mesa (digite -1 para cancelar a criacao de comanda): ");
                scanf("%d", &(comanda[c]).mesa.nummesa);
                if((comanda[c]).mesa.nummesa!=-1)
                {
                    totalpedidos[c] = 0;
                    comanda[c].precocomanda = 0;
                    printf("Digite o andar da mesa: ");
                    scanf("%d", &(comanda[c]).mesa.andarmesa);
                    int i = 0;
                    int numloop = 0;
                    do{
                        printf("\n");
                        if(numloop==0)
                            cardapio();
                        printf("\nDigite o numero do pedido (digite -1 para encerrar o pedido): ");
                        scanf("%d", &(comanda[c]).pedido[i].numpedido);
                        if(((comanda[c]).pedido[i].numpedido < 1 || (comanda[c]).pedido[i].numpedido > 6) && (comanda[c]).pedido[i].numpedido != -1)
                            printf("Esse numero nao esta no cardapio!\n");
                        else
                        {
                            if((comanda[c]).pedido[i].numpedido==-1)
                                i=-1;
                            else
                            {   
                                totalpedidos[c]++;
                                printf("Digite a quantidade desse pedido: ");
                                scanf("%d", &(comanda[c]).pedido[i].qtdpedido);
                                calculaprecocomanda((comanda[c]).pedido[i].numpedido, c, (comanda[c]).pedido[i].qtdpedido);
                                if(i<19)
                                    i++;
                                else
                                {
                                    printf("Comanda cheia!\n");
                                    i=-1;
                                    limpa
                                    printf("\nDigite enter para continuar.\n");
                                    getchar();
                                }
                            }
                        }
                        numloop++;
                    }while(i!=-1);
                }
                break;
            }
            else if(((comanda[c]).idcomanda == idatualizar && (comanda[c]).flagcomanda == 0) || c == quantidadecomanda-1)
            {
                printf("Comanda nao encontrada.\n");
                limpa
                printf("\nDigite enter para continuar.\n");
                getchar();
            }
        }
    }
}

