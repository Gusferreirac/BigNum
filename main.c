#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bigNum.h"

int main()
{
    int num1, num2;
    char *arquivo, *line;
    BigNum *bigNum1, *bigNum2;
    Lista *controllerA, *controllerB;
    FILE *arqIN, *arqOUT;

    controllerA = (Lista *)malloc(sizeof(Lista));
    controllerB = (Lista *)malloc(sizeof(Lista));

    bigNum1 = criar();
    controllerA->primeiro = bigNum1;

    bigNum2 = criar();
    controllerB->ultimo;

    gets(arquivo);

    arqIN = fopen(arquivo, "r");

    if (arqIN == NULL)
    {
        printf("Ocorreu um erro na abertura do arquivo!");
        system("pause");
        return 1;
    }

    fscanf(arqIN, "%d%d", &num1, &num2);

    while (num1 != 0 || num2 != 0)
    {
        intToBignum(num1, bigNum1, controllerA);
        intToBignum(num2, bigNum2, controllerB);
        fscanf(arqIN, "%d%d", &num1, &num2);
    }

    return 1;
}