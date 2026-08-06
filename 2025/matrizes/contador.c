#include<stdio.h>
#include<stdlib.h>

int main(){

  int matriz [3][4][5][6];
  int v = 1;

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        for (int l = 0; l < 6; l++)
        {
          matriz[i][j][k][l] = v++;
          printf("%d\n", matriz[i][j][k][l]);
        }
      }
    }    
  }
}