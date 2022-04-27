#include <stdlib.h>
#include <stdio.h>
#include "bigNum.h"

int main()
{
    BigNum *bigNum1, *bigNum2, *soma;
    Lista *controllerA, *controllerB, *controllerC;

    controllerA = (Lista *)malloc(sizeof(Lista));
    controllerB = (Lista *)malloc(sizeof(Lista));
    controllerC = (Lista *)malloc(sizeof(Lista));
    int a, b;

    bigNum1 = criar();
    controllerA->primeiro = bigNum1;

    bigNum2 = criar();
    controllerB->primeiro = bigNum2;

    soma = criar();
    controllerC->primeiro = soma;

    scanf("%d %d", &a, &b);

    controllerA->casas = intToBignum(a, bigNum1, controllerA);
    controllerB->casas = intToBignum(b, bigNum2, controllerB);

    // subtrair(controllerA, controllerB, soma, controllerC);
    fatorial(controllerA, controllerC);
    imprimeBignum(controllerC->ultimo);

    system("pause");
    return 0;
}