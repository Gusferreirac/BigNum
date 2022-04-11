#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bigNum.h"

struct elemento
{
    struct Lista *proximo;
    int num;
};

typedef struct elemento Elem;

Lista *criar()
{
    Lista *li = (Lista *)malloc(sizeof(Lista));

    if (li != NULL)
    {
        *li = NULL;
    }

    return li;
}

void destruir(Lista *bigNum)
{
    if (bigNum != NULL)
    {
        Elem *no;
        while ((*bigNum) != NULL)
        {
            no = *bigNum;
            *bigNum = (*bigNum)->proximo;
            free(no); // libera todos os nos primeiro
        }
        free(bigNum); // depois libera a lista
    }
}

Lista *intToBignum(int num)
{
    int casas = 1;
    int numClone;

    numClone = num;

    Elem *no = (Elem *)malloc(sizeof(Elem));

    while ((num = num / 10) > 0)
    {
        casas++;
    }

    while (casas != 0)
    {
        no->num = numClone / pow(10, (casas - 1));
        numClone = numClone - no->num * pow(10, (casas - 1));
        casas--;
        no = no->proximo;
    }
    no->proximo = NULL;
    return no;
}

Lista *somar(Elem *bigNumA, Elem *bigNumB)
{
    Elem *result = (Elem *)malloc(sizeof(Elem));
    int carrega = 0;

    while (bigNumA != NULL || bigNumB != NULL)
    {
        result->num = carrega;

        if (bigNumA == NULL) // se não tiver número nessa casa colocamos 0
        {
            bigNumA->num = 0;
        }

        if (bigNumB == NULL) // se não tiver número nessa casa colocamos 0
        {
            bigNumB->num = 0;
        }

        if ((result->num + bigNumA->num + bigNumB->num) >= 10) // se a soma for maior que 10 fazemos o "vai um"
        {
            result->num += (bigNumA->num + bigNumB->num) - 10;
            carrega = 1;
        }
        else
        {
            result->num += bigNumA->num + bigNumB->num;
            carrega = 0;
        }

        result = result->proximo;
        bigNumA = bigNumA->proximo;
        bigNumB = bigNumB->proximo;
    }

    return result;
}

Lista *subtrair(Elem *bigNumA, Elem *bigNumB)
{
}