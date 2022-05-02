#include <stdlib.h>
#include <stdio.h>
#include "bigNum.h"
#include "bigNumArithmetics.h"

int main()
{
    Lista *controllerA, *controllerB, *controllerC, *controllerAClone, *controllerD;

    controllerA = (Lista *)malloc(sizeof(Lista));
    controllerAClone = (Lista *)malloc(sizeof(Lista));
    controllerB = (Lista *)malloc(sizeof(Lista));
    controllerC = (Lista *)malloc(sizeof(Lista));
    controllerD = (Lista *)malloc(sizeof(Lista));
    int a, b;
    int i;

    scanf("%d %d", &a, &b);

    controllerA->casas = intToBignum(a, controllerA);
    controllerAClone->casas = intToBignum(a, controllerAClone);
    controllerB->casas = intToBignum(b, controllerB);
    //imprimeBignum(controllerA->ultimo);

    //somar(controllerA->primeiro, controllerB->primeiro, controllerC);
    //multiplicar(controllerA, controllerB,controllerC);
    //compara(controllerA, controllerB);
    fatorial(controllerA, controllerAClone, controllerC);
    dividir(controllerC,controllerB,controllerD);
    //subtrair(controllerA, controllerB,controllerC);
    //clone(controllerA,controllerC);
    //clone(controllerB,controllerC);
    // incrementa(controllerA);

    // dividir(controllerA, controllerB, controllerC);
    //  dividir(controllerC, controllerB, controllerC);
    //   controllerC->primeiro->anterior = NULL;
    imprimeBignum(controllerD->ultimo);

    destruir(controllerA->primeiro);
    destruir(controllerAClone->primeiro);
    destruir(controllerB->primeiro);
    destruir(controllerC->primeiro);
    destruir(controllerD->primeiro);
    free(controllerA);
    free(controllerAClone);
    free(controllerB);
    free(controllerC);
    free(controllerD);

    //system("pause");
    return 0;
}