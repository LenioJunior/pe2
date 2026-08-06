#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]){
    printf("Nome do programa: %s\n", argv[0]);

    if(argc != 2){
        printf("Você não informou o nome do arquivo!\n");
        return 1;
    }

    char * fileName = argv[1];
    printf("Argumento 1: %s\n", fileName);

    FILE * file = fopen(fileName, "w");

    if(file == NULL){
        printf("Ocorreu um erro ao abrir o arquivo!\n");
        return 1;
    }

    char c = '*';
    printf("Informe um caracter. * para sair.\n");
    do {
        c = getchar();        
        if(c == '*'){
            break;
        }
        putc(c, file);
        while(getchar() != '\n');
    } while(1);

    fclose(file);
    printf("Finalizando o programa!\n");
}