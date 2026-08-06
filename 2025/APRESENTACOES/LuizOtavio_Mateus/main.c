#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// ---------- variaveis globais:


int id[3]={0,0,0}; //auto incremento




// ---------- structs:


typedef struct pessoa{
   int idPessoa;
   char *nome;
   int idade;
} Pessoa;


typedef struct livro{
   int idLivro;
   char *titulo;
   char *autor;
   int quantidade;
   int restricao; //restricao de idade
   int disponibilidade;
} Livro;


typedef struct emprestimo{
   int idEmprestimo;
   Pessoa* cliente;
   int total_de_livros;
   Livro* emprestados[3];
   int data_emprestimo[3]; //{dia,mes,ano}
   int data_vencimento[3];
   int finalizado; // 1 -> verdadeiro 0 -> falso
} Emprestimo;




// ---------- prototipos:


Pessoa criaPessoa();
Livro criaLivro();
Emprestimo criaEmprestimo(Emprestimo* emprestimos,Pessoa* pessoas,Livro* livros,int* quantidades);
void mostraPessoa(Pessoa fulano);
void mostraVariasPessoas(Pessoa* lista_de_pessoas,int quantidade);
void mostraVariosLivros(Livro* lista_de_livros,int quantidade);
void mostraLivro(Livro livro);
void mudaQuantidade(Livro** livros,int id,int quantidade);
void salvar(Pessoa* pessoas,Livro* livros,Emprestimo* emprestimos,int quantidade[3]);
int achaPessoa(Pessoa* pessoas,int ID,int quantidade);
int achaLivro(Livro* livros,int ID,int quantidade);
void salvaPessoas(Pessoa* pessoas,int quantidade,FILE* arquivo);
void salvaLivros(Livro* livros,int quantidade,FILE* arquivo);
void salvaEmprestimos(Emprestimo* emprestimos,int quantidade,FILE* arquivo);
void geraRelatorio();
void relatorioPessoa(Pessoa fulano,FILE* arquivo);
void relatorioVariasPessoas(Pessoa* lista_de_pessoas,int quantidade,FILE* arquivo);
void relatorioVariosLivros(Livro* lista_de_livros,int quantidade,FILE* arquivo);
void relatorioLivro(Livro livro,FILE* arquivo);
void mostraEprestimo(Emprestimo emprestimo);
void mostraVariosEmprestimos(Emprestimo* emprestimos,int quantidade);
void relatorioEprestimo(Emprestimo emprestimo,FILE* arquivo);
void relatorioVariosEmprestimos(Emprestimo* emprestimos,int quantidade,FILE* arquivo);
int inicia(Pessoa** pessoas,Livro** livros,Emprestimo** emprestimos);
void iniciaLivros(Livro** livros,FILE* arquivo);
void iniciaPessoas(Pessoa** livros,FILE* arquivo);
void iniciaEmprestimos(Emprestimo** emprestimos,Pessoa* pessoas,Livro* livros,FILE* arquivo);
void concerta_emprestimo_pessoa(Emprestimo** emprestimos,int quantidade,int gambiarra);
void concerta_emprestimo_livro(Emprestimo** emprestimos,int quantidade,int gambiarra);




// ---------- funções basicas:


int contaCaractere(char *str){
   int contador=0;
  
   while(str[contador] != '\0'){
       contador++;
   }
  
   return contador+1; // +1 por causa do \0
}


void pause(){
   printf("\n\ndigite enter pra seguir...");
   getchar();
}


int Menu(Emprestimo **emprestimos, Pessoa **pessoas, Livro **livros,int quantidades[3]){
   int opcao,id_livro;
   Pessoa* realocacaoP;
   Livro* realocacaoL;
   Emprestimo* realocacaoE;
   printf("o que voce quer fazer?\n[1] adicionar pessoa\n[2] adicionar livro\n[3] adicionar ou remover exemplar de livro\n[4] ver pessoas cadastradas\n[5] ver livros cadastrados\n[6] cadastrae emprestimo\n[7] mostrar emprestimos\n[8] salvar\n[9] gerar relatorio\n[10] sair\n");
   scanf("%d",&opcao);
   while(getchar()!='\n');
   switch(opcao){
       case 1:
           (*pessoas)[quantidades[0]]=criaPessoa();
           quantidades[0]++;
           realocacaoP=realloc(*pessoas,(quantidades[0]+1)*sizeof(Pessoa));
           if(realocacaoP != NULL){
               concerta_emprestimo_pessoa(emprestimos,quantidades[2],realocacaoP-(*pessoas));
               *pessoas=realocacaoP;
           }
           else{
               printf("erro na alocacao ;-;");
           }
           return 1;
       case 2:
           (*livros)[quantidades[1]]=criaLivro();
           quantidades[1]++;
           realocacaoL=realloc(*livros,(quantidades[1]+1)*sizeof(Livro));
           concerta_emprestimo_pessoa(emprestimos,quantidades[2],realocacaoP-(*pessoas));
           if(realocacaoL != NULL){
               *livros=realocacaoL;
           }
           else{
               printf("erro na alocacao ;-;");
           }
           return 1;
       case 3:
           mostraVariosLivros(*livros,quantidades[1]);
           printf("qual o id do livro que você quer mudar\n");
           scanf("%d",&id_livro);
           mudaQuantidade(livros,id_livro,quantidades[1]);
           return 1;
       case 4:
           printf("\n\n");
           mostraVariasPessoas(*pessoas,quantidades[0]);
           pause();
           return 1;
       case 5:
           mostraVariosLivros(*livros,quantidades[1]);
           pause();
           break;
       case 6:
           (*emprestimos)[quantidades[2]]=criaEmprestimo(*emprestimos,*pessoas,*livros,quantidades);
           if((*emprestimos)[quantidades[2]].idEmprestimo == - 1){
               printf("\nemprestimo cancelado\n");
               pause();
           } else{
               quantidades[2]++;
               realocacaoE=realloc(*emprestimos,(quantidades[2]+1)*sizeof(Emprestimo));
               if(realocacaoE != NULL){
                   *emprestimos=realocacaoE;
               }
               else{
                   printf("erro na alocacao ;-;");
               }
           }
           return 1;
       case 7:
           mostraVariosEmprestimos(*emprestimos,quantidades[2]);
           pause();
           return 1;
       case 8:
           salvar(*pessoas,*livros,*emprestimos,quantidades);
           printf("dados salvos\n");
           return 1;
       case 9:
           geraRelatorio(*pessoas,*livros,*emprestimos,quantidades);
           return 1;
       case 10:
           return 0;
       default:
       printf("opcao invalida ;-;");
           break;
   }
   return 1;
}




// ---------- salvar:


void salvar(Pessoa* pessoas,Livro* livros,Emprestimo* emprestimos,int quantidade[3]){
   FILE* arquivo;
   arquivo = fopen("arquivo.bin","wb");
   salvaPessoas(pessoas,quantidade[0],arquivo);
   salvaLivros(livros,quantidade[1],arquivo);
   salvaEmprestimos(emprestimos,quantidade[2],arquivo);
   fclose(arquivo);
}


void salvaPessoas(Pessoa* pessoas,int quantidade,FILE* arquivo){
   int caracteres;
   fwrite(&quantidade,sizeof(int),1,arquivo);
   for(int c=0;c<quantidade;c++){
       fwrite(&(pessoas[c].idPessoa),sizeof(int),1,arquivo);
       caracteres=contaCaractere(pessoas[c].nome);
       fwrite(&caracteres,sizeof(int),1,arquivo);
       fwrite(pessoas[c].nome,caracteres,1,arquivo);
       fwrite(&(pessoas[c].idade),sizeof(int),1,arquivo);
   }
}


void salvaLivros(Livro* livros,int quantidade,FILE* arquivo){
   int caracteres;
   fwrite(&quantidade,sizeof(int),1,arquivo);
   for(int c=0;c<quantidade;c++){
       fwrite(&(livros[c].idLivro),sizeof(int),1,arquivo);
       caracteres=contaCaractere(livros[c].titulo);
       fwrite(&caracteres,sizeof(int),1,arquivo);
       fwrite(livros[c].titulo,caracteres,1,arquivo);
       caracteres=contaCaractere(livros[c].autor);
       fwrite(&caracteres,sizeof(int),1,arquivo);
       fwrite(livros[c].autor,caracteres,1,arquivo);
       fwrite(&(livros[c].quantidade),sizeof(int),1,arquivo);
       fwrite(&(livros[c].restricao),sizeof(int),1,arquivo);
       fwrite(&(livros[c].disponibilidade),sizeof(int),1,arquivo);
   }
}


void salvaEmprestimos(Emprestimo* emprestimos,int quantidade,FILE* arquivo){
       fwrite(&quantidade,sizeof(int),1,arquivo);
   for(int c=0;c<quantidade;c++){
       fwrite(&(emprestimos[c].idEmprestimo),sizeof(int),1,arquivo);
       fwrite(&(emprestimos[c].cliente->idPessoa),sizeof(int),1,arquivo);
       fwrite(&emprestimos[c].total_de_livros,sizeof(int),1,arquivo);
       for(int d=0;d<emprestimos[c].total_de_livros;d++){
           fwrite(&(emprestimos[c].emprestados[d]->idLivro),sizeof(int),1,arquivo);
       }
       fwrite(&(emprestimos[c].data_emprestimo[0]),sizeof(int),1,arquivo);
       fwrite(&(emprestimos[c].data_emprestimo[1]),sizeof(int),1,arquivo);
       fwrite(&(emprestimos[c].data_emprestimo[2]),sizeof(int),1,arquivo);
       fwrite(&(emprestimos[c].data_vencimento[0]),sizeof(int),1,arquivo);
       fwrite(&(emprestimos[c].data_vencimento[1]),sizeof(int),1,arquivo);
       fwrite(&(emprestimos[c].data_vencimento[2]),sizeof(int),1,arquivo);
       fwrite(&(emprestimos[c].finalizado),sizeof(int),1,arquivo);
   }
}


void geraRelatorio(Pessoa* pessoas,Livro* livros,Emprestimo* emprestimos,int quantidades[3]){
   FILE* arquivo;
   arquivo=fopen("relatorio.txt","w");
   relatorioVariasPessoas(pessoas,quantidades[0],arquivo);
   relatorioVariosLivros(livros,quantidades[1],arquivo);
   relatorioVariosEmprestimos(emprestimos,quantidades[2],arquivo);
   fclose(arquivo);
}


void relatorioPessoa(Pessoa fulano,FILE* arquivo){
   fprintf(arquivo,"%-2d | %-20s | %-4d\n",fulano.idPessoa,fulano.nome,fulano.idade);
}


void relatorioVariasPessoas(Pessoa* lista_de_pessoas,int quantidade,FILE* arquivo){
   fprintf(arquivo,"------- Pessoas ------\n");
   fprintf(arquivo,"%-2s | %-20s | %-4s\n", "ID", "Nome", "idade");
   for(int c=0;c<quantidade;c++){
       relatorioPessoa(lista_de_pessoas[c],arquivo);
   }
}


void relatorioVariosLivros(Livro* lista_de_livros,int quantidade,FILE *arquivo){
   fprintf(arquivo,"------- Livros ------\n");
   fprintf(arquivo,"%-2s | %-20s | %-20s | %-20s | %-20s | %-20s\n","ID","Titulo","autor","quantidade","restrição","disponibilidade");
   for(int c=0;c<quantidade;c++){
       relatorioLivro(lista_de_livros[c],arquivo);
   }


}


void relatorioLivro(Livro livro,FILE* arquivo){
   fprintf(arquivo,"%-2d | %-20s | %-20s | %-20d | %-19d| %-20d\n",livro.idLivro,livro.titulo,livro.autor,livro.quantidade,livro.restricao,livro.disponibilidade);
}


void relatorioEprestimo(Emprestimo emprestimo,FILE* arquivo){
   fprintf(arquivo,"%-2d | %-20s | %-20d | %-2d/%-2d/%-4d | %2d/%2d/%4d | %d\n",emprestimo.idEmprestimo,(*emprestimo.cliente).nome,emprestimo.total_de_livros,emprestimo.data_emprestimo[0],emprestimo.data_emprestimo[1],emprestimo.data_emprestimo[2],emprestimo.data_vencimento[0],emprestimo.data_vencimento[1],emprestimo.data_vencimento[2],emprestimo.finalizado);
}


void relatorioVariosEmprestimos(Emprestimo* emprestimos,int quantidade,FILE* arquivo){
   fprintf(arquivo,"------- livros ------\n");
   fprintf(arquivo,"%-2s | %-20s | %-20s | %-10s | %-10s | %-2s","ID","nome do cliente","total de livros","Data","fim","devolvido");
   for(int c=0;c<quantidade;c++){
       relatorioEprestimo(emprestimos[c],arquivo);
   }
}




// ---------- funções das structs:


Pessoa criaPessoa(){
   Pessoa nova;
   int tamanhoNome;
   char nome[100];
  
   nova.idPessoa=id[0];
   id[0]++;
  
   printf("qual o nome da pessoa?\n");
   fgets(nome,100,stdin);
   nome[strcspn(nome, "\n")] = '\0';
   tamanhoNome=contaCaractere(nome);
   nova.nome=malloc((tamanhoNome)*sizeof(char));
   for(int it=0;it<tamanhoNome;it++){
       nova.nome[it]=nome[it];
   }
  
   printf("qual a idade da pessoa?\n");
   scanf("%d",&nova.idade);
  
   return nova;
}


Livro criaLivro(){
   Livro novo;
   char texto[100];
   int tamanhoNome;
  
   novo.idLivro=id[1];
   id[1]++;
  
   printf("qual o titulo do livro?\n");
   fgets(texto,100,stdin);
   texto[strcspn(texto, "\n")] = '\0';
   tamanhoNome=contaCaractere(texto);
   novo.titulo=malloc(tamanhoNome*sizeof(char));
   for(int it=0;it<tamanhoNome;it++){
       novo.titulo[it]=texto[it];
   }
  
   printf("qual o nome do autor do livro?\n");
   fgets(texto,100,stdin);
   texto[strcspn(texto, "\n")] = '\0';
   tamanhoNome=contaCaractere(texto);
   novo.autor=malloc(tamanhoNome*sizeof(char));
   for(int it=0;it<tamanhoNome;it++){
       novo.autor[it]=texto[it];
   }
  
   printf("quantos exemplares tem?\n");
   scanf("%d",&novo.quantidade);
  
   printf("qual a idade minima para pegar o livro? (0 se nao tiver)\n");
   scanf("%d",&novo.restricao);
  
   novo.disponibilidade=novo.quantidade;
  
   return novo;
}


Emprestimo criaEmprestimo(Emprestimo* emprestimos,Pessoa* pessoas,Livro* livros,int* quantidades){
   char ch;
   Emprestimo novo;
   int id_obj,indice,quantidade_livro,c;
   char flag='i'; // i=inicial; c=concluido (operação concluida); s=sim (opção aceita); n=não (opção negada).
   time_t agora;
   struct tm *data_hora;


   time(&agora);
   data_hora = localtime(&agora);


   novo.idEmprestimo=id[2];
   id[2]++;
   mostraVariasPessoas(pessoas,quantidades[0]);
   while(flag != 'c'){
       indice=-1;
       flag='c';
       while(indice==-1){
           printf("qual o ID da pessoa que pegou o emprestimo?\n");
           scanf("%d",&id_obj);
           indice=achaPessoa(pessoas,id_obj,quantidades[0]);
           if(indice==-1){
               printf("id invalido\n");
               printf("desja tentar denovo? [s/n]\n");
               int ch;
               while ((ch = getchar()) != '\n' && ch != EOF);
               scanf("%c",&flag);
               while ((ch = getchar()) != '\n' && ch != EOF);


               if(flag == 'n'){
                   novo.idEmprestimo=-1;
                   id[2]--;
                   return novo;
               }
           }
       }
       for(c=0;c<quantidades[2];c++){
           if((emprestimos[c]).cliente == &(pessoas[indice])){
               printf("essa pessoa ja tem um emprestimo em andamento :/\n");
               printf("deseja tentar outra pessoa? [s/n]\n");


               while ((ch = getchar()) != '\n' && ch != EOF);
               scanf("%c",&flag);
               while ((ch = getchar()) != '\n' && ch != EOF);
           }
           if(flag=='n'){
               novo.idEmprestimo=-1;
               id[2]--;
               return novo;
       }
       }
   }
   flag='i';
   novo.cliente=&(pessoas[indice]);
   while(flag != 'c'){
       flag='c';
       indice=-1;
       printf("quantos livros ela pegou?\n");
       scanf("%d",&quantidade_livro);
       while(quantidade_livro >3){
           if(quantidade_livro > 3){
               printf("não é permitido pegar tantos livros\n");
           }
           printf("quantos livros ela pegou?\n");
           scanf("%d",&quantidade_livro);
       }
       if(quantidade_livro <= 0){
           novo.idEmprestimo=-1;
           id[2]--;
           return novo;
       }
       novo.total_de_livros=quantidade_livro;
       for(c=0;c<quantidade_livro;c++){
           mostraVariosLivros(livros,quantidades[1]);
           while(indice==-1){
               printf("qual o ID do livro que pegou o emprestimo?\n");
               scanf("%d",&id_obj);
               indice=achaLivro(livros,id_obj,quantidades[1]);
               if(indice==-1){
                   printf("id invalido\n");
                   printf("desja tentar denovo? [s/n]\n");
                   while ((ch = getchar()) != '\n' && ch != EOF);
                   scanf("%c",&flag);
                   while ((ch = getchar()) != '\n' && ch != EOF);
                   if(flag == 'n'){
                       novo.idEmprestimo=-1;
                       id[2]--;
                       return novo;
                   }
               }
           }
           if(livros[indice].disponibilidade==0){
               printf("\nesse livro esta indisponivel :/ \n");
               pause();
               c--;
           } else if(novo.cliente->idade < livros[indice].restricao){
               printf("\nessa pessoa não tem idade suficiente pra esse livro :/ \n");
               pause();
               c--;
           }
           livros[indice].disponibilidade--;
           novo.emprestados[c]=&(livros[indice]);
           indice=-1;
       }
   }
   novo.data_emprestimo[0]=(*data_hora).tm_mday;
   novo.data_emprestimo[1]=(*data_hora).tm_mon + 1;
   novo.data_emprestimo[2]=(*data_hora).tm_year + 1900;
   novo.data_vencimento[0]=((*data_hora).tm_mday + 14)%30; // 2 semanas sla
   if(novo.data_vencimento[0]==0){
       novo.data_vencimento[0]=30;
   }
   novo.data_vencimento[1]=(((*data_hora).tm_mon + 1) + (novo.data_vencimento[0]/30))%12;
   if(novo.data_vencimento[1]==0){
       novo.data_vencimento[1]=12;
   }
   novo.data_vencimento[2]=(*data_hora).tm_year + 1900 + (novo.data_vencimento[1]/12);
   novo.finalizado=0;


   return novo;
}


void concerta_emprestimo_pessoa(Emprestimo** emprestimos,int quantidade,int gambiarra){
   for(int c=0;c<quantidade;c++){
       (*emprestimos)[c].cliente+=gambiarra;
   }
}


void concerta_emprestimo_livro(Emprestimo** emprestimos,int quantidade,int gambiarra){
   for(int c=0;c<quantidade;c++){
       for(int d=0; d<(*emprestimos)[c].total_de_livros;d++){


           (*emprestimos)[c].emprestados[d]+=gambiarra;
       }
   }
}


int achaPessoa(Pessoa* pessoas,int ID,int quantidade){
   int c;
   for(c=0;c<quantidade;c++){
       if((pessoas)[c].idPessoa==ID){
           return c;
       }
   }
   return -1;
}


int achaLivro(Livro* livros,int ID,int quantidade){
   int c;
   for(c=0;c<quantidade;c++){
       if((livros)[c].idLivro==ID){
           return c;
       }
   }
   return -1;
}


void mostraPessoa(Pessoa fulano){
   printf("%-2d | %-20s | %-4d\n",fulano.idPessoa,fulano.nome,fulano.idade);
}


void mostraVariasPessoas(Pessoa* lista_de_pessoas,int quantidade){
   printf("%-2s | %-20s | %-4s\n", "ID", "Nome", "idade");
   for(int c=0;c<quantidade;c++){
       mostraPessoa(lista_de_pessoas[c]);
   }
}


void mostraVariosLivros(Livro* lista_de_livros,int quantidade){
   printf("%-2s | %-20s | %-20s | %-20s | %-20s | %-20s\n","ID","Titulo","autor","quantidade","restrição","disponibilidade");
   for(int c=0;c<quantidade;c++){
       mostraLivro(lista_de_livros[c]);
   }


}


void mostraLivro(Livro livro){
   printf("%-2d | %-20s | %-20s | %-20d | %-19d| %-20d\n",livro.idLivro,livro.titulo,livro.autor,livro.quantidade,livro.restricao,livro.disponibilidade);
}


void mostraEprestimo(Emprestimo emprestimo){
   printf("%-2d | %-20s | %-20d | %-2d/%-2d/%-4d | %2d/%2d/%4d | %d\n",emprestimo.idEmprestimo,(*emprestimo.cliente).nome,emprestimo.total_de_livros,emprestimo.data_emprestimo[0],emprestimo.data_emprestimo[1],emprestimo.data_emprestimo[2],emprestimo.data_vencimento[0],emprestimo.data_vencimento[1],emprestimo.data_vencimento[2],emprestimo.finalizado);
}


void mostraVariosEmprestimos(Emprestimo* emprestimos,int quantidade){
   printf("%-2s | %-20s | %-20s | %-10s | %-10s | %-2s\n","ID","nome do cliente","total de livros","Data","fim","devolvido");
   for(int c=0;c<quantidade;c++){
       mostraEprestimo(emprestimos[c]);
   }
}


void mudaQuantidade(Livro** livros,int ID,int quantidade){
   int c,flag=0,quantidade_alterada;
   for(c=0;c<quantidade;c++){
       if((*livros)[c].idLivro==ID){
           break;
       }
       flag=1;
   }
   if(flag){
       printf("não existe livro com o ID informado ;-;");
   }
   else{
       printf("quantidade atual: %d\nquantos você quer mudar??\n",(*livros)[c].quantidade);
       scanf("%d",&quantidade_alterada);
       (*livros)[c].quantidade-=quantidade_alterada;
       (*livros)[c].disponibilidade-=quantidade_alterada;
   }
}








// ----------inicializa:


int inicia(Pessoa** pessoas,Livro** livros,Emprestimo** emprestimos){


   FILE* arquivo;
   arquivo=fopen("arquivo.bin","rb");
   if (!arquivo){
       return 0;
   } else{
       iniciaPessoas(pessoas,arquivo);
       iniciaLivros(livros,arquivo);
       iniciaEmprestimos(emprestimos,*pessoas,*livros,arquivo);
       fclose(arquivo);
       return 1;
   }
}


void iniciaPessoas(Pessoa** pessoas,FILE* arquivo){
   int quantidade;
   int caracteres;
   Pessoa* intermediaria;
   fread(&quantidade,sizeof(int),1,arquivo);
   id[0]=quantidade;
   intermediaria=realloc(*pessoas,(quantidade+1)*sizeof(Pessoa));
   *pessoas=intermediaria; // valeria uma verificação aqui mas eu to sem tempo
   for(int c=0;c<quantidade;c++){


       fread(&(*pessoas)[c].idPessoa,sizeof(int),1,arquivo);
       fread(&caracteres,sizeof(int),1,arquivo);
       (*pessoas)[c].nome=malloc(caracteres*sizeof(char));
       fread((*pessoas)[c].nome,caracteres,1,arquivo);
       fread(&(*pessoas)[c].idade,sizeof(int),1,arquivo);
   }
}


void iniciaLivros(Livro** livros,FILE* arquivo){
   int caracteres;
   int quantidade;
   Livro* intermediario;
   fread(&quantidade,sizeof(int),1,arquivo);
   id[1]=quantidade;
   intermediario=realloc(*livros,(quantidade+1)*sizeof(Livro));
   *livros=intermediario; // valeria uma verificação aqui mas sem tempo pra polir
   for(int c=0;c<quantidade;c++){
       fread(&(*livros)[c].idLivro,sizeof(int),1,arquivo);
       fread(&caracteres,sizeof(int),1,arquivo);
       (*livros)[c].titulo=malloc(caracteres*sizeof(char));
       fread((*livros)[c].titulo,caracteres,1,arquivo);
       fread(&caracteres,sizeof(int),1,arquivo);
       (*livros)[c].autor=malloc(caracteres*sizeof(char));
       fread((*livros)[c].autor,caracteres,1,arquivo);
       fread(&(*livros)[c].quantidade,sizeof(int),1,arquivo);
       fread(&(*livros)[c].restricao,sizeof(int),1,arquivo);
       fread(&(*livros)[c].disponibilidade,sizeof(int),1,arquivo);
   }
}


void iniciaEmprestimos(Emprestimo** emprestimos,Pessoa* pessoas,Livro* livros,FILE* arquivo){
   int quantidade;
   Emprestimo* intermediario;
   fread(&quantidade,sizeof(int),1,arquivo);
   id[2]=quantidade;
   intermediario=realloc(*emprestimos,(quantidade+1)*sizeof(Emprestimo));
   *emprestimos=intermediario;
   int id_pessoa,id_livro,indice;
   for(int c=0;c<quantidade;c++){
       fread(&(*emprestimos)[c].idEmprestimo,sizeof(int),1,arquivo);
       fread(&id_pessoa,sizeof(int),1,arquivo);
       indice=achaPessoa(pessoas,id_pessoa,id[0]);
       (*emprestimos)[c].cliente=&pessoas[indice];
       fread(&(*emprestimos)[c].total_de_livros,sizeof(int),1,arquivo);
       for(int d=0;d<(*emprestimos)[c].total_de_livros;d++){
           fread(&id_livro,sizeof(int),1,arquivo);
           indice=achaLivro(livros,id_livro,id[1]);
           (*emprestimos)[c].emprestados[d]=&livros[indice];
       }
       fread(&(*emprestimos)[c].data_emprestimo[0],sizeof(int),1,arquivo);
       fread(&(*emprestimos)[c].data_emprestimo[1],sizeof(int),1,arquivo);
       fread(&(*emprestimos)[c].data_emprestimo[2],sizeof(int),1,arquivo);
       fread(&(*emprestimos)[c].data_vencimento[0],sizeof(int),1,arquivo);
       fread(&(*emprestimos)[c].data_vencimento[1],sizeof(int),1,arquivo);
       fread(&(*emprestimos)[c].data_vencimento[2],sizeof(int),1,arquivo);
       fread(&(*emprestimos)[c].finalizado,sizeof(int),1,arquivo);
   }
}




// ---------- execução:


int main()
{
   int flag;
   Pessoa *pessoas;
   Livro *livros;
   Emprestimo* emprestimos;
   pessoas=malloc(sizeof(Pessoa));
   livros=malloc(sizeof(Livro));
   emprestimos=malloc(sizeof(Emprestimo));
   int quantidade[3]; //{pessoa,livro,emprestimo}
   inicia(&pessoas,&livros,&emprestimos);
   quantidade[0]=id[0];
   quantidade[1]=id[1];
   quantidade[2]=id[2];
   do{
       flag=Menu(&emprestimos,&pessoas,&livros,quantidade);
   }while(flag != 0);
   return 0;
}


