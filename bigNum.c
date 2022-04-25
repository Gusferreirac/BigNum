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
    list->primeiro = result;
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

    // A primeira coisa que devemos fazer é verificar se o subtrator é maior ou menor que o subtraendo
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
    // fim da verificação

    // se o subtrador realmente for maior que o subtraendo trocamos os dois e deixamos o negative como 1, que significa que o resultado sera negativo
    // ex: 10 - 30 = (30 - 10)*(-1)
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

    while (bigNumA != NULL || bigNumB != NULL) // A subtração somente para quando os dois numeros acabam
    {
        if (bigNumB != NULL)
        {
            if ((bigNumA->num - bigNumB->num) < 0) // se a subtração for menor que zero teremos que pegar emprestado na casa ao lado
            {
                aux = bigNumA->proximo;
                while (aux != NULL)
                {
                    if (aux->num > 0) // quando encontrar o primeiro numero maior que zero vamos tirar 1
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
                result->num = bigNumA->num - bigNumB->num; // se a sbutração não for < 0 basta fazer normalmente
            }
            bigNumA = bigNumA->proximo;
            bigNumB = bigNumB->proximo;
        }
        else
        {
            result->num = bigNumA->num; // se o subtrator tiver chegado ao fim o resultado recebe o resto do subtraendo
            bigNumA = bigNumA->proximo;
        }
        result->proximo = (BigNum *)malloc(sizeof(BigNum));
        result->proximo->anterior = result;
        result = result->proximo;
    }

    result = result->anterior;
    result->proximo = NULL;
    removerZeros(result, list); // removemos os zeros a esquerda e aplicamos o sinal negativo no que sobrou
    if (negative == 1)
    {
        list->ultimo->num = list->ultimo->num * -1;
    }
}

void multiplicar(Lista *bigNumAHead, Lista *bigNumBHead, BigNum **res, Lista *list)
{
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumA = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumB = (BigNum *)malloc(sizeof(BigNum));
    Lista *controllerParcialResult = (Lista *)malloc(sizeof(Lista));

    bigNumA = bigNumAHead->primeiro->proximo;
    bigNumB = bigNumBHead->primeiro->proximo;

    result->num = 0;
    result->anterior = NULL;
    result->proximo = NULL;
    list->primeiro = result;

    int carrega = 0;
    int salta = 0;
    int i = 0;

    while (bigNumA != NULL)
    {
        BigNum *parcialResult = (BigNum *)malloc(sizeof(BigNum));
        parcialResult->num = 0;
        parcialResult->anterior = NULL;
        controllerParcialResult->primeiro = parcialResult;

        if (salta > 0)
        {
            for (i = 0; i < salta; i++) // a medida que as operações vão indo colocamos zeros no incio na hora da soma
            {
                parcialResult->num = 0;
                parcialResult->proximo = (BigNum *)malloc(sizeof(BigNum));
                parcialResult->proximo->anterior = parcialResult;
                parcialResult = parcialResult->proximo;
            }
        }
        while (bigNumB != NULL)
        {
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

            parcialResult->proximo = (BigNum *)malloc(sizeof(BigNum));
            parcialResult->proximo->anterior = parcialResult;
            parcialResult = parcialResult->proximo;
            parcialResult->num = carrega;
        }
        bigNumB = bigNumBHead->primeiro->proximo;
        salta++;

        if (carrega > 0)
        {
            parcialResult->num = carrega;
        }
        else
        {
            parcialResult = parcialResult->anterior;
        }
        parcialResult->proximo = NULL;
        controllerParcialResult->ultimo = parcialResult;

        BigNum *aux = (BigNum *)malloc(sizeof(BigNum));
        somar(controllerParcialResult->primeiro, list->primeiro, aux, list);
        result = list->primeiro;
        destruir(parcialResult);
        free(parcialResult);
        bigNumA = bigNumA->proximo;
    }
}

BigNum *dividir(BigNum *numerador, BigNum *divisor)
{
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