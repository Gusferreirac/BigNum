#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bigNum.h"

void somar(BigNum *bigNumAHead, BigNum *bigNumBHead, Lista *list)
{
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumA;
    BigNum *bigNumB;
    int carrega = 0;

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
        free(result->proximo);
    }

    result->proximo = NULL;
    list->ultimo = result;
}

void subtrair(Lista *bigNumAHead, Lista *bigNumBHead, Lista *list)
{
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumA;
    BigNum *bigNumB;
    BigNum *aux;

    int carrega = 0;
    int negative = 0;

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
            BigNum *auxA;
            BigNum *auxB;

            auxA = bigNumAHead->ultimo;
            auxB = bigNumBHead->ultimo;

            while (auxA != NULL && auxB != NULL)
            {
                if (auxA->num < auxB->num)
                {
                    negative = 1;
                    break;
                }
                else if (auxA->num > auxB->num)
                {
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
        bigNumA = bigNumBHead->primeiro;
        bigNumB = bigNumAHead->primeiro;
    }
    else
    {
        bigNumA = bigNumAHead->primeiro;
        bigNumB = bigNumBHead->primeiro;
    }

    result->anterior = NULL;
    list->primeiro = result;

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
    free(result->proximo);
    result->proximo = NULL;
    list->ultimo = result;
    list->casas = contaCasas(list);
    removerZeros(result, list); // removemos os zeros a esquerda e aplicamos o sinal negativo no que sobrou
    if (negative == 1)
    {
        list->ultimo->num = list->ultimo->num * -1;
    }
}

void multiplicar(Lista *bigNumAHead, Lista *bigNumBHead, Lista *list) //*Multiplicação OK!
{
    BigNum *result;
    BigNum *bigNumA;
    BigNum *bigNumB;
    Lista *controllerParcialResult = (Lista *)malloc(sizeof(Lista));

    bigNumA = bigNumAHead->primeiro;
    bigNumB = bigNumBHead->primeiro;

    result = criar();
    list->primeiro = result;
    list->ultimo = result;

    int carrega = 0;
    int salta = 0;
    int i = 0;

    while (bigNumA != NULL)
    {
        BigNum *parcialResult; // resultado parcial (que sera feito a soma depois)
        parcialResult = criar();
        controllerParcialResult->primeiro = parcialResult;

        if (salta > 0)
        {
            for (i = 0; i < salta; i++) // a medida que as operações vão indo colocamos zeros no incio na hora da soma
            {
                parcialResult->proximo = (BigNum *)malloc(sizeof(BigNum));
                parcialResult->proximo->anterior = parcialResult;
                parcialResult = parcialResult->proximo;
                parcialResult->num = 0;
            }
            parcialResult->proximo = NULL;
            controllerParcialResult->ultimo = parcialResult;
        }
        while (bigNumB != NULL)
        {
            if (bigNumB->num * bigNumA->num >= 10) // verifica se a multplicação é maior que 10
            {
                carrega = (bigNumB->num * bigNumA->num) / 10; // se for maior que 10 carrega a casa do decimal para a proxima casa
                parcialResult->num += (bigNumB->num * bigNumA->num) % 10;
            }
            else
            {
                carrega = 0;
                parcialResult->num += bigNumB->num * bigNumA->num; // caso nao for > 10 a multiplicacao será feita normalmente
            }
            bigNumB = bigNumB->proximo;

            parcialResult->proximo = (BigNum *)malloc(sizeof(BigNum));
            parcialResult->proximo->anterior = parcialResult;
            parcialResult = parcialResult->proximo;
            parcialResult->num = carrega;
        }
        bigNumB = bigNumBHead->primeiro;
        salta++;

        if (carrega > 0)
        {
            parcialResult->num = carrega; // se sobrou um carrega no ultimo o numero recebe esse carrega
        }
        else
        {
            parcialResult = parcialResult->anterior;
            free(parcialResult->proximo);
        }
        parcialResult->proximo = NULL;
        controllerParcialResult->ultimo = parcialResult;

        somar(controllerParcialResult->primeiro, result, list); // fazemos as somas dos parcialResult
        destruir(result);
        result = list->primeiro;
        destruir(controllerParcialResult->primeiro);
        bigNumA = bigNumA->proximo;
    }

    free(controllerParcialResult);
    list->casas = contaCasas(list);
}

void dividir(Lista *numerador, Lista *divisor, Lista *resultController)
{
    BigNum *clone;
    BigNum *result;
    BigNum *numeradorNum;
    Lista *numeradorParcial = (Lista *)malloc(sizeof(Lista));
    Lista *quocient = (Lista *)malloc(sizeof(Lista));
    Lista *multiplicador = (Lista *)malloc(sizeof(Lista));
    Lista *guess = (Lista *)malloc(sizeof(Lista));
    Lista *resto = (Lista *)malloc(sizeof(Lista));
    Lista *restoClone = (Lista *)malloc(sizeof(Lista));

    int i, multi, end = 0, maior = 0, menor = 0;

    result = criar();

    numeradorParcial->casas = 0;

    numeradorNum = numerador->ultimo;

    //---------------------------VERIFICA SE DIVISOR > NUMERADOR-------------------------------
    //-------------------------------OU SE DIVISOR = NUMERADOR---------------------------------
    if (numerador->casas < divisor->casas)
    {
        maior = 1;
    }
    else if (numerador->casas == divisor->casas)
    {
        if (numerador->ultimo->num < divisor->ultimo->num)
        {
            maior = 1;
        }
        else if (numerador->ultimo->num == divisor->ultimo->num)
        {
            BigNum *auxA = (BigNum *)malloc(sizeof(BigNum));
            BigNum *auxB = (BigNum *)malloc(sizeof(BigNum));

            auxA = numerador->ultimo;
            auxB = divisor->ultimo;

            while (auxA != NULL && auxB != NULL)
            {
                if (auxA->num < auxB->num)
                {
                    maior = 1;
                    break;
                }

                if (auxA->num > auxB->num)
                {
                    menor = 1;
                    break;
                }
                auxA = auxA->anterior;
                auxB = auxB->anterior;
            }

            if (maior != 1 && menor != 1)
            {
                result->num = 1;
                resultController->primeiro = result;
                resultController->ultimo = result;
                return;
            }
        }
    }

    if (maior == 1)
    {
        resultController->primeiro = result;
        resultController->ultimo = result;
        return;
    }
    // --------------------------------------- FIM DA VERIFICAÇÃO -------------------------------------------------- //

    free(result);

    for (i = 0; i < divisor->casas; i++)
    {
        clone = criar();
        clone->num = numeradorNum->num;
        insereNoInicio(numeradorParcial, clone);
        numeradorNum = numeradorNum->anterior;
    }

    for (i = 0; i < 10; i++)
    {
        multiplicador->casas = intToBignum(i, multiplicador);
        multiplicar(divisor, multiplicador, guess);
        if (compara(guess, numeradorParcial) == 1)
        {
            break;
        }
        destruir(multiplicador->primeiro);
        destruir(guess->primeiro);
    }

    multi = i - 1;
    destruir(multiplicador->primeiro);
    destruir(guess->primeiro);

    BigNum *aux;
    aux = criar();
    aux->num = multi;
    resultController->casas = 0;
    insereNoInicio(resultController, aux);
    multiplicar(divisor, resultController, guess);
    numeradorParcial->casas = contaCasas(numeradorParcial);
    guess->casas = contaCasas(guess);
    subtrair(numeradorParcial, guess, resto);
    destruir(guess->primeiro);
    int count = 0;

    while (numeradorNum != NULL)
    {
        clone = criar();
        clone->num = numeradorNum->num;
        insereNoInicio(resto, clone);
        removerZeros(resto->ultimo, resto);

        for (i = 0; i <= 10; i++)
        {
            multiplicador->casas = intToBignum(i, multiplicador);
            multiplicar(divisor, multiplicador, guess);
            removerZeros(guess->ultimo, guess);
            resto->casas = contaCasas(resto);
            guess->casas = contaCasas(guess);
            if (compara(guess, resto) == 1)
            {
                break;
            }
            destruir(multiplicador->primeiro);
            destruir(guess->primeiro);
        }

        multi = i - 1;
        destruir(multiplicador->primeiro);
        destruir(guess->primeiro);

        BigNum *aux;
        aux = criar();
        aux->num = multi;
        multiplicador->casas = intToBignum(i - 1, multiplicador);

        insereNoInicio(resultController, aux);

        multiplicar(divisor, multiplicador, guess);
        destruir(multiplicador->primeiro);

        removerZeros(guess->ultimo, guess);
        resto->casas = contaCasas(resto);
        guess->casas = contaCasas(guess);
        subtrair(resto, guess, restoClone);
        destruir(guess->primeiro);
        destruir(resto->primeiro);
        clonar(restoClone, resto);
        destruir(restoClone->primeiro);

        numeradorNum = numeradorNum->anterior;
    }

    removerZeros(resultController->ultimo, resultController);

    destruir(numeradorParcial->primeiro);
    destruir(resto->primeiro);
    free(numeradorParcial);
    free(guess);
    free(quocient);
    free(multiplicador);
    free(resto);
    free(restoClone);
}

void fatorial(Lista *num, Lista *numClone, Lista *result) //*Fatorial OK!
{
    BigNum *um;
    BigNum *aux;
    Lista *controllerUm = (Lista *)malloc(sizeof(Lista));
    Lista *controllerAux = (Lista *)malloc(sizeof(Lista));
    Lista *controllerAuxClone = (Lista *)malloc(sizeof(Lista));
    Lista *parcialResult = (Lista *)malloc(sizeof(Lista));
    int end = 0;

    um = criar();
    um->num = 1;

    controllerUm->primeiro = um;
    controllerUm->ultimo = um;
    controllerUm->casas = 1;

    subtrair(num, controllerUm, controllerAux);
    multiplicar(controllerAux, numClone, result);

    while (end != 1)
    {
        subtrair(controllerAux, controllerUm, controllerAuxClone);
        destruir(controllerAux->primeiro);
        clonar(controllerAuxClone, controllerAux);
        destruir(controllerAuxClone->primeiro);

        if (controllerAux->primeiro->num == 0 && controllerAux->primeiro == controllerAux->ultimo)
        {
            end = 1;
        }
        else
        {
            clonar(result, parcialResult);
            destruir(result->primeiro);
            multiplicar(controllerAux, parcialResult, result);
            destruir(parcialResult->primeiro);
        }
    }

    destruir(controllerAux->primeiro);
    destruir(controllerUm->primeiro);
    free(parcialResult);
    free(controllerAux);
    free(controllerAuxClone);
    free(controllerUm);
}
