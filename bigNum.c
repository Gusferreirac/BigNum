#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bigNum.h"

struct elemento
{
    struct Lista *proximo;
    struct Lista *anterior;
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

void intToBignum(Lista *bigNum, int num)
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
}