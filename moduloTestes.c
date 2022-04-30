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
    imprimeBignum(controllerA->ultimo);

    //  subtrair(controllerA, controllerB, soma, controllerC);
    //  multiplicar(controllerA, controllerB, soma, controllerC);
    // fatorial(controllerA, controllerAClone, controllerC);
    // incrementa(controllerA);

    // dividir(controllerA, controllerB, controllerC);
    //  dividir(controllerC, controllerB, controllerC);
    //   controllerC->primeiro->anterior = NULL;
    //imprimeBignum(controllerC->ultimo);

    destruir(controllerA->primeiro);
    destruir(controllerB->primeiro);
    freeLista(controllerA);
    freeLista(controllerAClone);
    freeLista(controllerB);
    freeLista(controllerC);

    system("pause");
    return 0;
}