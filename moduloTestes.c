#include <stdlib.h>
#include <stdio.h>
#include "bigNum.h"
#include "bigNumArithmetics.h"

int main()
{
    BigNum *bigNum1, *bigNum2, *soma;
    Lista *controllerA, *controllerB, *controllerC, *controllerAClone;

    controllerA = (Lista *)malloc(sizeof(Lista));
    controllerAClone = (Lista *)malloc(sizeof(Lista));
    controllerB = (Lista *)malloc(sizeof(Lista));
    controllerC = (Lista *)malloc(sizeof(Lista));
    int a, b;
    int i;

    bigNum1 = criar();
    controllerA->primeiro = bigNum1;

    bigNum2 = criar();
    controllerB->primeiro = bigNum2;

    soma = criar();
    controllerC->primeiro = soma;
    controllerC->ultimo = soma;

    scanf("%d %d", &a, &b);

    controllerA->casas = intToBignum(a, controllerA);
    controllerAClone->casas = intToBignum(a, controllerAClone);
    controllerB->casas = intToBignum(b, controllerB);
    imprimeBignum(controllerA->ultimo);
    system("pause");

    //  subtrair(controllerA, controllerB, soma, controllerC);
    //  multiplicar(controllerA, controllerB, soma, controllerC);
    // fatorial(controllerA, controllerAClone, controllerC);
    // incrementa(controllerA);

    // dividir(controllerA, controllerB, controllerC);
    //  dividir(controllerC, controllerB, controllerC);
    //   controllerC->primeiro->anterior = NULL;
    imprimeBignum(controllerC->ultimo);

    destruir(bigNum1);
    destruir(bigNum2);
    free(controllerA);
    free(controllerB);
    free(controllerC);

    system("pause");
    return 0;
}