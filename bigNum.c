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

int *intToBignum(int num, BigNum **head, Lista *list)
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
    return tam;
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
    while (bigNumA != NULL || bigNumB != NULL) // A soma somente para quando os dois numeros acabam
    {
        result->num = carrega; // A variavel carrega contem o "vai um" da iteração anterior

        if (bigNumA != NULL && bigNumB != NULL)
        {
            if ((result->num + bigNumA->num + bigNumB->num) >= 10) // se a soma for maior que 10 fazemos o "vai um"
            {
                result->num += (bigNumA->num + bigNumB->num) - 10; // vai um e deixa o resto
                carrega = 1;
            }
            else
            {
                result->num += bigNumA->num + bigNumB->num; // se a soma nao explode basta fazer normalmente
                carrega = 0;
            }
            bigNumA = bigNumA->proximo;
            bigNumB = bigNumB->proximo;
        }
        else
        {
            if (bigNumA == NULL) // se um dos numeros chegar ao fim o resultado recebera o outro mais o "vai um" se tiver
            {
                if ((result->num + bigNumB->num) >= 10) // se a soma do numero restante com o vai um explodir fazemos o vai um de novo e deixamos o resto
                {
                    result->num += bigNumB->num - 10;
                    carrega = 1;
                }
                else
                {
                    result->num += bigNumB->num; // caso nao basta somar normal
                    carrega = 0;
                }

                bigNumB = bigNumB->proximo; // como o numero A ja terminou somente percorremos o numero B
            }
            else // o mesmo processo visto acima porem desta vez o numero que sobrou foi o A
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

        if (bigNumA == NULL && bigNumB == NULL) // se os dois numeros chegaram ao fim a ultima casa do resultado recebe o ultimo vai um
        {
            result->num = carrega; // se a ultima soma explodiu a ultima casa do resultado recebera 1 caso nao recebera 0 o que nao muda o resultado (0 a esq.)
        }
    }
    if (result->num == 0)
    {
        result = result->anterior; // tirando o zero a esquerda
    }
    result->proximo = NULL;
    list->ultimo = result;
}

void subtrair(Lista *bigNumAHead, Lista *bigNumBHead, BigNum **res, Lista *list)
{
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumA = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumB = (BigNum *)malloc(sizeof(BigNum));
    BigNum *aux = (BigNum *)malloc(sizeof(BigNum));

    int carrega = 0;
    int negative = 0;

    *res = result;
    if (bigNumAHead->casas < bigNumBHead->casas)
    {
        negative = 1;
    }
    else if (bigNumAHead->casas == bigNumBHead->casas)
    {
        if (bigNumAHead->ultimo->num < bigNumBHead->ultimo->num)
        {
            negative = 1;
        }
        else if (bigNumAHead->ultimo->num == bigNumBHead->ultimo->num)
        {
            BigNum *auxA = (BigNum *)malloc(sizeof(BigNum));
            BigNum *auxB = (BigNum *)malloc(sizeof(BigNum));

            auxA = bigNumAHead->ultimo;
            auxB = bigNumBHead->ultimo;

            while (auxA != NULL && auxB != NULL)
            {
                if (auxA->num < auxB->num)
                {
                    negative = 1;
                    break;
                }
                auxA = auxA->anterior;
                auxB = auxB->anterior;
            }
        }
    }

    if (negative == 1)
    {
        bigNumA = bigNumBHead->primeiro->proximo;
        bigNumB = bigNumAHead->primeiro->proximo;
    }
    else
    {
        bigNumA = bigNumAHead->primeiro->proximo;
        bigNumB = bigNumBHead->primeiro->proximo;
    }

    result->anterior = NULL;

    while (bigNumA != NULL || bigNumB != NULL) // A soma somente para quando os dois numeros acabam
    {
        if (bigNumB != NULL)
        {
            if ((bigNumA->num - bigNumB->num) < 0) // se a soma for maior que 10 fazemos o "vai um"
            {
                aux = bigNumA->proximo;
                while (aux != NULL)
                {
                    if (aux->num > 0)
                    {
                        aux->num--;
                        break;
                    }
                    else
                    {
                        aux->num = 9;
                    }
                    aux = aux->proximo;
                }

                result->num = (bigNumA->num + 10) - bigNumB->num;
            }
            else
            {
                result->num = bigNumA->num - bigNumB->num; // se a soma nao explode basta fazer normalmente
            }
            bigNumA = bigNumA->proximo;
            bigNumB = bigNumB->proximo;
        }
        else
        {
            result->num = bigNumA->num;
            bigNumA = bigNumA->proximo;
        }
        result->proximo = (BigNum *)malloc(sizeof(BigNum));
        result->proximo->anterior = result;
        result = result->proximo;
    }

    result = result->anterior;
    result->proximo = NULL;
    removerZeros(result, list);
    if (negative == 1)
    {
        list->ultimo->num = list->ultimo->num * -1;
    }
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
        printf("%d ", no->num);
        no = no->anterior;
    }
}

void removerZeros(BigNum *bigNum, Lista *controller)
{
    while (bigNum != NULL)
    {
        if (bigNum->anterior == NULL || bigNum->num != 0)
        {
            bigNum->proximo = NULL;
            break;
        }
        bigNum = bigNum->anterior;
        free(bigNum->proximo);
    }
    controller->ultimo = bigNum;
}