#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bigNum.h"

int main()
{
    int num1, num2;
    char *arquivo, *line;
    Lista *bigNum1, *bignum2;
    FILE *arqIN, *arqOUT;

    bigNum1 = criar();
    bignum2 = criar();

    gets(arquivo);

    arqIN = fopen(arquivo, "r");

    if (arqIN == NULL)
    {
        printf("Ocorreu um erro na abertura do arquivo!");
        system("pause");
        return 1;
    }

    while (fscanf(arqIN, "%d%d", &num1, &num2) != EOF)
    {
        bigNum1 = intToBignum(num1);
        bignum2 = intToBignum(num2);
    }

    return 1;
}