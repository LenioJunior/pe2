#ifndef STRUCT_PESSOA_H
#define STRUCT_PESSOA_H

#include<stdlib.h>

typedef struct carro Carro;

Carro * criar();
void preenche(Carro * carro);
void exibe(Carro * carro);

#endif