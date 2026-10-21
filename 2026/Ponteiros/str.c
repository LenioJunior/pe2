#include <stdio.h>
#include <stdlib.h>

char *concatenar(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return NULL;

    int size1 = 0;
    int size2 = 0;

    char *bs1 = s1;
    char *bs2 = s2;

    while (s1 != NULL && *s1 != '\0')
    {
        size1++;
        s1++;
    }

    while (s2 != NULL && *s2 != '\0')
    {
        size2++;
        s2++;
    }

    char *res = malloc(((size1 + size2) * sizeof(char)) + 1);
    char *pres = res;

    s1 = bs1;
    s2 = bs2;

    while (s1 != NULL && *s1 != '\0')
    {
        *res = *s1;
        res++;
        s1++;
    }

    while (s2 != NULL && *s2 != '\0')
    {
        *res = *s2;
        res++;
        s2++;
    }

    *res = '\0';

    printf("Dentro: %s\n", pres);

    return pres;
}

int main()
{
    char f1[] = "Meu";
    char f2[] = "Nome";
    char *concat = concatenar(f1, f2);

    printf("Resultado: %s\n", concat);

    return 0;
}