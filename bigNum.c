#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bigNum.h"
#include "randomTools.h"

BigNum *criar()
{
    BigNum *bigNum = (BigNum *)malloc(sizeof(BigNum));

    bigNum->num = 0;
    bigNum->anterior = NULL;
    bigNum->proximo = NULL;
    return bigNum;
}

// Recebe o primeiro nó da lista e libera a lista
void destruir(BigNum *bigNum)
{
    if (bigNum != NULL)
    {
        BigNum *no;
        while (bigNum != NULL)
        {
            no = bigNum;
            bigNum = bigNum->proximo;
            free(no); // libera todos os nos primeiro
        }
        free(bigNum); // depois libera a BigNum
    }
}

int intToBignum(int num, Lista *list)
{
    int casas = 1;
    int tam, i = 0;
    int numClone;
    char buffer[5];

    BigNum *no = (BigNum *)malloc(sizeof(BigNum));

    no->anterior = NULL;
    list->primeiro = no;

    sprintf(buffer, "%d", num);
    // itoa(num, buffer, 10);
    reverseString(buffer);
    tam = strlen(buffer);

    for (i = 0; i < tam; i++)
    {
        no->num = buffer[i] - '0';
        if (i != (tam - 1))
        {
            no->proximo = (BigNum *)malloc(sizeof(BigNum));
            no->proximo->anterior = no;
            no = no->proximo;
        }
    }

    no->proximo = NULL;
    list->ultimo = no;
    //freeNo(no);
    return tam;
}

int contaCasas(Lista *li)
{
    BigNum *a;
    int casas = 0;

    a = li->primeiro;

    while (a != NULL)
    {
        casas++;
        a = a->proximo;
    }

    return casas;
}

void incrementa(Lista *li)
{
    BigNum *a = (BigNum *)malloc(sizeof(BigNum));
    BigNum *b = (BigNum *)malloc(sizeof(BigNum));
    int i, casas = 0;

    a = li->primeiro;

    if (a->num != 9)
    {
        a->num++;
    }
    else
    {
        while (a != NULL)
        {
            if (a->proximo == NULL)
            {
                a->proximo = (BigNum *)malloc(sizeof(BigNum));
                a->proximo->anterior = a;
                a->proximo->num = 1;
                a = a->proximo;
                li->ultimo = a;
                li->casas++;
                b = li->ultimo;
                while (b->anterior != NULL)
                {
                    b = b->anterior;
                    b->num = 0;
                }

                return;
            }

            a = a->proximo;
            if (a->num < 9)
            {
                a->num = a->num + 1;
                b = a;
                while (b->anterior != NULL)
                {
                    b = b->anterior;
                    b->num = 0;
                }

                return;
            }
        }
    }
}

// Se a > b retorna 1 caso nao retorna 0
int compara(Lista *a, Lista *b)
{
    printf("NumeradorParcial ");
    imprimeBignum(b->ultimo);
    printf("\n\n");
    if (b->casas < a->casas)
    {
        return 1;
    }
    else if (b->casas == a->casas)
    {
        if (b->ultimo->num < a->ultimo->num)
        {
            return 1;
        }
        else if (b->ultimo->num == a->ultimo->num)
        {
            BigNum *auxA = (BigNum *)malloc(sizeof(BigNum));
            BigNum *auxB = (BigNum *)malloc(sizeof(BigNum));

            auxA = b->ultimo;
            auxB = a->ultimo;

            while (auxA != NULL && auxB != NULL)
            {

                if (auxA->num < auxB->num)
                {
                    return 1;
                    break;
                }
                else if (auxA->num > auxB->num)
                {
                    return 0;
                }

                auxA = auxA->anterior;
                auxB = auxB->anterior;
            }

            destruir(auxA);
            destruir(auxB);
        }
    }

    return 0;
}

void insereElemento(Lista *controller, BigNum *num)
{
    if (controller->casas == 0)
    {
        controller->primeiro = num;
        controller->ultimo = num;
        controller->primeiro->anterior = NULL;
        controller->ultimo->proximo = NULL;
        controller->casas++;
        return;
    }
    controller->ultimo->proximo = num;
    num->anterior = controller->ultimo;
    num->proximo = NULL;
    controller->ultimo = num;
    controller->casas++;
}

// Clona a em b
void clone(Lista *a, Lista *b)
{
    BigNum *num;
    BigNum *numClone;

    num = a->primeiro;

    numClone = criar();
    b->primeiro = numClone;

    while (num != NULL)
    {
        //printf("A");
        numClone->num = num->num;
        num = num->proximo;
        numClone->proximo = (BigNum *)malloc(sizeof(BigNum));
        numClone->proximo->anterior = numClone;
        numClone = numClone->proximo;
    }
    numClone = numClone->anterior;
    free(numClone->proximo);
    numClone->proximo = NULL;
    b->ultimo = numClone;
}

void imprimeBignum(BigNum *Num)
{
    BigNum *no = Num;
    // printf("\n");
    while (no != NULL)
    {
        printf("%d ", no->num);
        no = no->anterior;
    }
}

void removerZeros(BigNum *bigNum, Lista *controller)
{
    while (bigNum != NULL)
    {
        if (bigNum->anterior == NULL || bigNum->num != 0) // o loop percorre ate chegar no inicio da lista ou ate achar um numero != 0
        {
            bigNum->proximo = NULL;
            break;
        }
        bigNum = bigNum->anterior; // enquanto não acha um num != 0 ou chega no inicio da lista removemos os 0
        free(bigNum->proximo);
    }
    controller->ultimo = bigNum;
}

void freeLista(Lista *li){
    free(li->primeiro);
    free(li->ultimo);
    free(li);
}

void freeNo(BigNum *no){
    free(no->anterior);
    free(no->proximo);
    free(no);
}