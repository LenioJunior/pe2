#include<stdio.h>

int main(int argc, char * args[]){

  if (argc > 0) {
    for (int i = 0; i < argc; i++)
    {
      printf("Argumento %d: %s\n", i, args[i]);
    }
  }
}