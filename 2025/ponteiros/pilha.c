#include<stdio.h>
#include<stdlib.h>
#define SIZE 5

void push (int i );
int pop ( void );

int * tos , * p1 , stack [ SIZE ];

int main(){

  int value ;
  tos = stack ;
  p1 = stack ;

  do {
    printf ( " Digite o valor : " );
    scanf("%d", &value);
    if( value !=0) {
      push ( value );
    }
    else {
      printf ("O valor do topo eh %d\n" , pop ());
    }
  } while ( value != -1);
}

void push (int i ){  
  if(p1 == (tos + SIZE)){
    printf ("Estouro de Pilha");
    exit (1);
  }
  *p1 = i ;
  p1++;
}

int pop ( ){
  p1--;
  if( p1 < tos ){
    printf ("Estouro de pilha");
    exit (1);
  }
  return *p1;
}