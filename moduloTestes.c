#include <stdlib.h>
#include <stdio.h>
#include "bigNum.h"

int main()
{
    BigNum *bigNum1, *bigNum2, *soma;
    Lista *controller;

    controller = (Lista *)malloc(sizeof(Lista));
    int a, b;

    bigNum1 = criar();
    controller->primeiro = bigNum1;
    controller->ultimo = bigNum1;
    // bigNum2 = criar();
    // soma = criar();

    scanf("%d", &a);

    intToBignum(a, bigNum1, controller);
    imprimeBignum(controller->ultimo);
    //   imprimir(controller->ultimo);
    //   intToBignum(b, bigNum2);

    // soma = somar(bigNum1, bigNum2);

    // imprimeBignum(soma);

    system("pause");
    return 0;
}