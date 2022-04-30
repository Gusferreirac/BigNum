#include <stdlib.h>
#include <stdio.h>
#include "bigNum.h"
#include "bigNumArithmetics.h"

int main()
{
    Lista *controllerA, *controllerB, *controllerC, *controllerAClone;

    controllerA = (Lista *)malloc(sizeof(Lista));
    controllerAClone = (Lista *)malloc(sizeof(Lista));
    controllerB = (Lista *)malloc(sizeof(Lista));
    controllerC = (Lista *)malloc(sizeof(Lista));
    int a, b;
    int i;

    scanf("%d %d", &a, &b);

    controllerA->casas = intToBignum(a, controllerA);
    //controllerAClone->casas = intToBignum(a, controllerAClone);
    controllerB->casas = intToBignum(b, controllerB);
    //imprimeBignum(controllerA->ultimo);

    //somar(controllerA->primeiro, controllerB->primeiro, controllerC);
    multiplicar(controllerA, controllerB,controllerC);
    //subtrair(controllerA, controllerB,controllerC);
    // fatorial(controllerA, controllerAClone, controllerC);
    // incrementa(controllerA);

    // dividir(controllerA, controllerB, controllerC);
    //  dividir(controllerC, controllerB, controllerC);
    //   controllerC->primeiro->anterior = NULL;
    imprimeBignum(controllerC->ultimo);

    destruir(controllerA->primeiro);
    destruir(controllerB->primeiro);
    destruir(controllerC->primeiro);
    free(controllerA);
    free(controllerAClone);
    free(controllerB);
    free(controllerC);

    //system("pause");
    return 0;
}