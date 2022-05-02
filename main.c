#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bigNum.h"
#include "bigNumArithmetics.h"

int main()
{
    int num1, num2, i = 0;
    char arquivo[10], *line;
    BigNum *bigNum1, *bigNum2, *bigNum3;
    Lista *controllerA, *controllerAClone, *controllerB, *controllerC, *controllerD, *controllerE, *result, *resultClone;
    FILE *arqIN;

    controllerA = (Lista *)malloc(sizeof(Lista));
    controllerAClone = (Lista *)malloc(sizeof(Lista));
    controllerB = (Lista *)malloc(sizeof(Lista));
    controllerC = (Lista *)malloc(sizeof(Lista));
    controllerD = (Lista *)malloc(sizeof(Lista));
    controllerE = (Lista *)malloc(sizeof(Lista));
    result = (Lista *)malloc(sizeof(Lista));
    resultClone = (Lista *)malloc(sizeof(Lista));

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
        if (num1 == num2)
        {
            printf("Não é possível dividir por zero!");
            system("pause");
            return 1;
        }

        i++;

        controllerA->casas = intToBignum(num1, controllerA);           // controllerA = n;
        controllerAClone->casas = intToBignum(num1, controllerAClone); // controllerA = n;
        controllerB->casas = intToBignum(num2, controllerB);           // controllerA = m

        subtrair(controllerAClone, controllerB, controllerC); // controllerC = n-m
        destruir(controllerAClone->primeiro);
        clonar(controllerC, controllerD); // controllerD = n-m

        fatorial(controllerC, controllerD, controllerE); // controllerE = (n-m)!
        destruir(controllerC->primeiro);
        destruir(controllerD->primeiro);

        clonar(controllerB, controllerC); // controllerC = m

        fatorial(controllerB, controllerC, controllerD); // controllerD = m!
        destruir(controllerB->primeiro);
        destruir(controllerC->primeiro);

        multiplicar(controllerE, controllerD, controllerC); // controllerC = m!(n-m)!
        destruir(controllerD->primeiro);
        destruir(controllerE->primeiro);

        clonar(controllerA, controllerD);                // controllerD = n
        fatorial(controllerA, controllerD, controllerE); // controllerE = n!
        destruir(controllerD->primeiro);
        destruir(controllerA->primeiro);

        controllerC->casas = contaCasas(controllerC);
        controllerE->casas = contaCasas(controllerE);
        dividir(controllerE, controllerC, controllerD); // controllerD = n!/m!(n-m)!

        if (i != 1)
        {
            if ((i % 2) == 0)
            {
                result->casas = contaCasas(result);
                controllerD->casas = contaCasas(controllerD);
                subtrair(result, controllerD, resultClone);
                destruir(result->primeiro);
                clonar(resultClone, result);
                destruir(resultClone->primeiro);
            }
            else
            {
                somar(result->primeiro, controllerD->primeiro, resultClone);
                destruir(result->primeiro);
                clonar(resultClone, result);
                destruir(resultClone->primeiro);
            }
        }
        else
        {
            clonar(controllerD, result);
        }

        destruir(controllerC->primeiro);
        destruir(controllerD->primeiro);
        destruir(controllerE->primeiro);
        fscanf(arqIN, "%d%d", &num1, &num2);
    }

    imprimeBignum(result->ultimo);

    destruir(result->primeiro);
    free(controllerA);
    free(controllerAClone);
    free(controllerB);
    free(controllerC);
    free(controllerD);
    free(controllerE);
    free(result);
    free(resultClone);

    return 1;
}