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
    FILE *arqIN, *arqOUT;

    controllerA = (Lista *)malloc(sizeof(Lista));
    controllerAClone = (Lista *)malloc(sizeof(Lista));
    controllerB = (Lista *)malloc(sizeof(Lista));
    controllerC = (Lista *)malloc(sizeof(Lista));
    controllerD = (Lista *)malloc(sizeof(Lista));
    controllerE = (Lista *)malloc(sizeof(Lista));
    result = (Lista *)malloc(sizeof(Lista));
    resultClone = (Lista *)malloc(sizeof(Lista));

    // bigNum1 = criar();
    // controllerA->primeiro = bigNum1;

    // bigNum2 = criar();
    // controllerB->ultimo;

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

        //printf("A ");
        controllerA->casas = intToBignum(num1, controllerA); // controllerA = n;
        controllerAClone->casas = intToBignum(num1, controllerAClone); // controllerA = n;
        controllerB->casas = intToBignum(num2, controllerB); // controllerA = m
        //resultClone->casas = intToBignum(0,resultClone);

        //printf("B ");
        //imprimeBignum(controllerA->ultimo);
        //printf("   ");
        subtrair(controllerAClone, controllerB, controllerC); // controllerC = n-m
        destruir(controllerAClone->primeiro);
        //imprimeBignum(controllerA->ultimo);
        //printf("   ");
        //printf("C ");
        clonar(controllerC, controllerD); // controllerD = n-m
        //printf("D ");
        fatorial(controllerC, controllerD, controllerE); // controllerE = (n-m)!
        //printf("E ");
        destruir(controllerC->primeiro);
        destruir(controllerD->primeiro);
        //printf("F ");
        clonar(controllerB, controllerC); // controllerC = m
        //printf("G ");
        fatorial(controllerB, controllerC, controllerD); // controllerD = m!
        //printf("H ");
        destruir(controllerB->primeiro);
        destruir(controllerC->primeiro);
        //printf("I ");
        multiplicar(controllerE, controllerD, controllerC); // controllerC = m!(n-m)!
        //printf("J ");
        destruir(controllerD->primeiro);
        destruir(controllerE->primeiro);
        //printf("K ");
        clonar(controllerA, controllerD); // controllerD = n
        //printf("L ");
        // imprimeBignum(controllerA->ultimo);
        // printf("   ");
        fatorial(controllerA, controllerD, controllerE); // controllerE = n!
        // imprimeBignum(controllerE->ultimo);
        // printf("   ");
        //printf("M ");
        destruir(controllerD->primeiro);
        destruir(controllerA->primeiro);
        //printf("N ");
        controllerC->casas = contaCasas(controllerC);
        controllerE->casas = contaCasas(controllerE);
        dividir(controllerE, controllerC, controllerD); // controllerD = n!/m!(n-m)!
        //printf("O ");

        if (i != 1)
        {
            if ((i % 2) == 0)
            {   
                // printf("%d", result->primeiro->num);
                // printf("%d", controllerD->primeiro->num);
                // imprimeBignum(result->ultimo);
                // printf("  ");
                // imprimeBignum(controllerD->ultimo);
                // printf("\n");

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

        //destruir(controllerA->primeiro);
        //destruir(controllerB->primeiro);
        destruir(controllerC->primeiro);
        destruir(controllerD->primeiro);
        destruir(controllerE->primeiro);
        fscanf(arqIN, "%d%d", &num1, &num2);
        //printf("X\n");
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