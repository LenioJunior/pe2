#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char gravar[100];
    char ler[100];
    int opcao;

    do {
        printf("Informe 1 para gravar. 2 para ler do arquivo. 3 para sair.\n");    
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            file = fopen("string.txt", "w");
            int condicao;
            if (file == NULL)
            {
                printf("Não foi possível abrir o arquivo.\n");
                return -1;
            }
            getchar();
            do {
                printf("Informe uma frase. Vazio para sair.\n");
                gets(gravar);
                strcat(gravar, "\n");
                fputs(gravar, file);
            } while (*gravar != ' ');

            rewind(file);

            char leitura[100];

            while (!feof(file))
            {
                fgets(leitura, 99, file);
                puts(leitura);
            }
            
        }
        else
        {
            file = fopen("string.txt", "r");
            if (file == NULL)
            {
                printf("Não foi possível abrir o arquivo.\n");
                return -1;
            }
            printf("Valores lidos:\n");
            char *result;
            while (result != NULL){
                result = fgets(ler, 100, file);                
                puts(ler);
            } 

        }
        fclose(file);
    } while(opcao != 3);
}