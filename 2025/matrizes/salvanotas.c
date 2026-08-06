#include<stdio.h>
#include<stdlib.h>

int mostraIds(int multi [2][2][2]){
  for (int i = 0; i < 2; i++)
  {
    printf("Id dos aluno '%d': %d\n", (i+1), multi [i][0][0]);
  }
  printf("--------------");
}

int mostraNotas(int multi [2][2][2]){
  for (int i = 0; i < 2; i++)
  {
    printf("Nota dos aluno '%d': %d\n", (i+1), multi [i][0][0]);
    for (int j = 0; j < 2; j++)
    {
      for (int k = 0; k < 2; k++)
      {
        if(!(j==0 && k==0))
          printf("Disciplina: '%d': %d\n", (i+1), multi [i][j][k]);
      }      
    }
    printf("--------------");
  }  
}

int main(){
  int multi [2][2][2];

  // IDs dos alunos
  multi[0][0][0] = 1000;
  multi[1][0][0] = 2000;

  // Notas do aluno 1
  multi[0][0][1] = 7;
  multi[0][1][0] = 9;
  multi[0][1][1] = 5;

  // Notas do aluno 2
  multi[1][0][1] = 5;
  multi[1][1][0] = 6;
  multi[1][1][1] = 3;

  mostraIds(multi);
  mostraNotas(multi);
}