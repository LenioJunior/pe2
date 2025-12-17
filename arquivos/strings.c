#include <stdio.h>
#include <stdlib.h>

struct struct_type {
   float balance ;
   char name [80];
} cust ;

int main()
{
   FILE * file = fopen("MyFile.txt", "w+");
   char frase[] = "Essa e uma frase qualquer";

   struct struct_type leitor;

   fwrite(&cust, sizeof(struct struct_type), 1, file);
   fread(&leitor, sizeof(struct struct_type), 1, file);

   fputs(frase, file);
   fclose(file);

   file = fopen("MyFile.txt", "a+");
   fseek(file, 0, SEEK_SET);
   char outrafrase[] = "Outra frase qualquer";

   fputs(outrafrase, file);
   fclose(file);

   remove("MyFile.txt");
}