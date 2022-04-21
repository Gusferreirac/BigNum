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

    intToBignum(a, bigNum1, controllerA);
    intToBignum(b, bigNum2, controllerB);

    somar(controllerA->primeiro->proximo, controllerB->primeiro->proximo, soma, controllerC);

    imprimeBignum(controllerC->ultimo);

    system("pause");
    return 0;
}