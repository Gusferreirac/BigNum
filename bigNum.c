#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bigNum.h"

BigNum *criar()
{
    BigNum *bigNum = (BigNum *)malloc(sizeof(BigNum));

    bigNum->num = 0;
    bigNum->anterior = NULL;
    bigNum->proximo = NULL;
    return bigNum;
}

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

void *intToBignum(int num, BigNum **head, Lista *list)
{
    int casas = 1;
    int tam, i = 0;
    int numClone;
    char buffer[5];

    BigNum *no = (BigNum *)malloc(sizeof(BigNum));
    BigNum *aux = (BigNum *)malloc(sizeof(BigNum));

    *head = no;

    no->anterior = NULL;

    itoa(num, buffer, 10);
    strrev(buffer);
    tam = strlen(buffer);

    for (i = 0; i < tam; i++)
    {
        no->num = buffer[i] - '0';
        if (i != (tam - 1))
        {
            no->proximo = (BigNum *)malloc(sizeof(BigNum));
            aux = no;
            no = no->proximo;
            no->anterior = aux;
        }
    }

    no->proximo = NULL;
    list->ultimo = no;
}

void somar(BigNum *bigNumAHead, BigNum *bigNumBHead, BigNum **res, Lista *list)
{
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumA = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumB = (BigNum *)malloc(sizeof(BigNum));
    int carrega = 0;

    *res = result;
    bigNumA = bigNumAHead;
    bigNumB = bigNumBHead;

    result->anterior = NULL;
    while (bigNumA != NULL || bigNumB != NULL)
    {
        result->num = carrega;

        if (bigNumA != NULL && bigNumB != NULL)
        {
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
            bigNumA = bigNumA->proximo;
            bigNumB = bigNumB->proximo;
        }
        else
        {
            if (bigNumA == NULL)
            {
                if ((result->num + bigNumB->num) >= 10)
                {
                    result->num += bigNumB->num - 10;
                    carrega = 1;
                }
                else
                {
                    result->num += bigNumB->num;
                    carrega = 0;
                }

                bigNumB = bigNumB->proximo;
            }
            else
            {
                if ((result->num + bigNumA->num) >= 10)
                {
                    result->num += bigNumA->num - 10;
                    carrega = 1;
                }
                else
                {
                    result->num += bigNumA->num;
                    carrega = 0;
                }

                bigNumA = bigNumA->proximo;
            }
        }
        result->proximo = (BigNum *)malloc(sizeof(BigNum));
        result->proximo->anterior = result;
        result = result->proximo;
        if (bigNumA == NULL && bigNumB == NULL)
        {
            result->num = carrega;
        }
    }

    result->proximo = NULL;
    list->ultimo = result;
}

BigNum *subtrair(BigNum *bigNumA, BigNum *bigNumB)
{
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    int carrega = 0;

    while (bigNumA != NULL || bigNumB != NULL)
    {

        if (bigNumA == NULL) // se o número do qual estamos subtraindo tiver chegado ao fim apenas iremos copiar o valor do subtraendo no resultado
        {
            if (bigNumB->proximo == NULL)
            {
                result->num = bigNumB->num * (-1); // se for o ultimo numero ele recebera o valor negativo
            }
            else
            {
                result->num = bigNumB->num;
            }
        }
        else if (bigNumB == NULL)
        {
            result->num = bigNumA->num;
        }
        else
        {
            if ((bigNumA->num - bigNumB->num) < 0) // se a subtracao for menor que zero avançamos nas casa decimais e encontramos o primeiro valor > 0 e tiramos um dele e pegamos "emprestado"
            {
                BigNum *aux = (BigNum *)malloc(sizeof(BigNum));
                aux = bigNumA;
                while (aux != NULL)
                {
                    if (aux->num > 0)
                    {
                        aux->num--;
                        carrega = 1;
                        break;
                    }
                    aux = aux->proximo;
                }
                if (carrega == 1)
                {
                    result->num = (bigNumA->num + 10) - bigNumB->num;
                }
                else
                {
                    if (bigNumB->proximo == NULL)
                    {
                        result->num = (bigNumA->num - bigNumB->num);
                    }
                    else
                    {
                        result->num = (bigNumA->num - bigNumB->num) * (-1);
                    }
                }
            }
            else
            {
                result->num = bigNumA->num - bigNumB->num;
            }
        }

        result = result->proximo;
        bigNumA = bigNumA->proximo;
        bigNumB = bigNumB->proximo;
    }

    return result;
}

BigNum *multiplicar(BigNum *bigNumA, BigNum *bigNumB)
{
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    result->num = 0;

    int carrega = 0;
    int salta = 0;
    int i = 0;

    while (bigNumA != NULL)
    {
        BigNum *parcialResult = (BigNum *)malloc(sizeof(BigNum));
        while (bigNumB != NULL)
        {
            if (salta > 0)
            {
                for (i = 0; i < salta; i++)
                {
                    parcialResult->num = 0;
                    parcialResult->proximo;
                }
            }
            else
            {
                if ((bigNumB->num + carrega) >= 10)
                {
                    bigNumB->proximo->num = (bigNumB->num + carrega) / 10; //
                }
                else
                {
                    bigNumB->num += carrega;
                }

                if (bigNumA->num == 0)
                {
                    break;
                }

                if (bigNumB->num * bigNumA->num >= 10) // verifica se a multplicação é maior que 10
                {
                    carrega = (bigNumB->num * bigNumA->num) / 10;
                    parcialResult->num += (bigNumB->num * bigNumA->num) % 10;
                }
                else
                {
                    carrega = 0;
                    parcialResult->num += bigNumB->num * bigNumA->num;
                }
                bigNumB = bigNumB->proximo;
                parcialResult = parcialResult->proximo;
            }
        }
        salta++;
        // result = somar(parcialResult, result);
        destruir(parcialResult);
        bigNumA = bigNumA->proximo;
    }
    return result;
}

void imprimeBignum(BigNum *Num)
{
    BigNum *no = Num;
    printf("\n");
    while (no != NULL)
    {
        printf("%d", no->num);
        no = no->anterior;
    }
}