#ifndef STRUCT_ALUNO_H
#define STRUCT_ALUNO_H

#define TAMANHO 3

typedef struct aluno {
  char * nome;
  char * matricula;
  float media;
  float notas[];
} Aluno;

Aluno * criar(int quantidade);
void lerNotas(Aluno * a, int tamanho);
void exibirNotas(Aluno * a, int tamanho);
float calcularMedia(Aluno * a, int tamanho);

#endif