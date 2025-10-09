typedef enum cor {
  AZUL = 10,
  AMARELO = 20,
  PRETO = 30
} Cor;

char * printaCor(enum cor cor){
  switch (cor)
  {
  case 10:
    return "Azul";
  case 20:
    return "Amarelo";  
  case 30:
    return "Preto";  
  default:
    break;
  }
}

int main(){
  Cor cor = AZUL;
  printf("Cor: %s\n\n\n", printaCor(cor));

  cor = PRETO;
  printf("Cor: %s\n\n\n", printaCor(cor));
}