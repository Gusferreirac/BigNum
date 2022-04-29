#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bigNum.h"

int main()
{
    int num1, num2, i = 0;
    char arquivo[10], *line;
    BigNum *bigNum1, *bigNum2, *bigNum3;
    Lista *controllerA, *controllerB, *controllerC, *controllerD, *controllerE, *result, *resultClone;
    FILE *arqIN, *arqOUT;

    controllerA = (Lista *)malloc(sizeof(Lista));
    controllerB = (Lista *)malloc(sizeof(Lista));
    controllerC = (Lista *)malloc(sizeof(Lista));
    controllerD = (Lista *)malloc(sizeof(Lista));
    controllerE = (Lista *)malloc(sizeof(Lista));
    result = (Lista *)malloc(sizeof(Lista));
    resultClone = (Lista *)malloc(sizeof(Lista));

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
        if (num1 == num2)
        {
            printf("Não é possível dividir por zero!");
            system("pause");
            return 1;
        }

        i++;

        printf("A ");
        controllerA->casas = intToBignum(num1, bigNum1, controllerA); // controllerA = n;
        controllerB->casas = intToBignum(num2, bigNum2, controllerB); // controllerA = m
        printf("B ");
        subtrair(controllerA, controllerB, controllerC); // controllerC = n-m
        printf("C ");
        clone(controllerC, controllerD); // controllerD = n-m
        printf("D ");
        fatorial(controllerC, controllerD, controllerE); // controllerE = (n-m)!
        printf("E ");
        destruir(controllerC->primeiro);
        destruir(controllerD->primeiro);
        printf("F ");
        clone(controllerB, controllerC); // controllerC = m
        printf("G ");
        fatorial(controllerB, controllerC, controllerD); // controllerD = m!
        printf("H ");
        destruir(controllerC->primeiro);
        printf("I ");
        multiplicar(controllerE, controllerD, controllerC); // controllerC = m!(n-m)!
        printf("J ");
        destruir(controllerD->primeiro);
        destruir(controllerE->primeiro);
        printf("K ");
        clone(controllerA, controllerD); // controllerD = n
        printf("L ");
        fatorial(controllerA, controllerD, controllerE); // controllerE = n!
        printf("M ");
        destruir(controllerD->primeiro);
        printf("N ");
        dividir(controllerE, controllerC, controllerD); // controllerD = n!/m!(n-m)!
        printf("O ");

        if (i != 1)
        {
            if ((i % 2) == 0)
            {
                clone(result, resultClone);
                subtrair(resultClone, controllerD, result);
            }
            else
            {
                clone(result, resultClone);
                somar(resultClone, controllerD, result);
            }
        }
        else
        {
            clone(controllerD, result);
        }

        destruir(controllerA->primeiro);
        destruir(controllerB->primeiro);
        destruir(controllerC->primeiro);
        destruir(controllerD->primeiro);
        destruir(controllerE->primeiro);
        fscanf(arqIN, "%d%d", &num1, &num2);
        printf("X\n");
    }

    imprimeBignum(result->ultimo);

    return 1;
}