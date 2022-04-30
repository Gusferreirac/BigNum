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

    //*res = result;

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
    removerZeros(result, list); // removemos os zeros a esquerda e aplicamos o sinal negativo no que sobrou
    if (negative == 1)
    {
        list->ultimo->num = list->ultimo->num * -1;
    }

    // while (result->anterior != NULL)
    // {
    //     list->casas++;
    //     result = result->anterior;
    // }

    // printf("\n\n");
    // printf("Resultado:");
    // imprimeBignum(list->ultimo);
    // printf("\n\n");

}

void multiplicar(Lista *bigNumAHead, Lista *bigNumBHead, Lista *list) //*Multiplicação OK!
{
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    BigNum *bigNumA;
    BigNum *bigNumB;
    Lista *controllerParcialResult = (Lista *)malloc(sizeof(Lista));

    // printf("\n");
    // imprimeBignum(bigNumAHead->ultimo);
    // imprimeBignum(bigNumBHead->ultimo);
    // printf("\n");

    bigNumA = bigNumAHead->primeiro;
    bigNumB = bigNumBHead->primeiro;

    result->num = 0;
    result->anterior = NULL;
    result->proximo = NULL;
    list->primeiro = result;
    list->ultimo = result;

    // if (bigNumAHead->casas != 1 && bigNumBHead->casas != 1)
    // {
    //     printf("Entrei! %d e %d\n", bigNumAHead->casas, bigNumBHead->casas);
    //     list->casas = bigNumAHead->casas + bigNumBHead->casas;
    // }
    // else if (bigNumAHead->casas == 1)
    // {
    //     list->casas = bigNumBHead->casas;
    // }
    // else
    // {
    //     list->casas = bigNumAHead->casas;
    // }

    int carrega = 0;
    int salta = 0;
    int i = 0;

    while (bigNumA != NULL)
    {
        BigNum *parcialResult = (BigNum *)malloc(sizeof(BigNum)); // resultado parcial (que sera feito a soma depois)
        parcialResult->num = 0;
        parcialResult->anterior = NULL;
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

        somar(controllerParcialResult->primeiro, list->primeiro, list); // fazemos as somas dos parcialResult
        free(result);
        result = list->primeiro;
        destruir(controllerParcialResult->primeiro);
        bigNumA = bigNumA->proximo;
    }

    free(controllerParcialResult);
    list->casas = contaCasas(list);
    // printf(" = ");
    // imprimeBignum(list->ultimo);
}

void dividir(Lista *numerador, Lista *divisor, Lista *resultController)
{
    BigNum *clone;
    BigNum *result = (BigNum *)malloc(sizeof(BigNum));
    BigNum *numeradorNum = (BigNum *)malloc(sizeof(BigNum));
    BigNum *divisorNum = (BigNum *)malloc(sizeof(BigNum));
    Lista *numeradorParcial = (Lista *)malloc(sizeof(Lista *));
    Lista *quocient = (Lista *)malloc(sizeof(Lista *));
    Lista *multiplicador = (Lista *)malloc(sizeof(Lista *));
    Lista *guess = (Lista *)malloc(sizeof(Lista *));
    Lista *resto = (Lista *)malloc(sizeof(Lista *));

    int i, multi, end = 0, maior = 0, menor = 0;

    result = criar();
    numeradorNum = criar();
    divisorNum = criar();

    numeradorParcial->casas = 0;

    numeradorNum = numerador->ultimo;
    divisorNum = divisor->ultimo;

    //---------------------------VERIFICA SE DIVISOR > NUMERADOR-------------------------------
    //-------------------------------OU SE DIVISOR = NUMERADOR---------------------------------
    if (numerador->casas < divisor->casas)
    {
        printf("1");
        maior = 1;
    }
    else if (numerador->casas == divisor->casas)
    {
        if (numerador->ultimo->num < divisor->ultimo->num)
        {
            printf("2");
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
                    printf("3");
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

    for (i = 0; i < divisor->casas; i++)
    {
        clone = (BigNum *)malloc(sizeof(BigNum));
        clone = criar();
        clone->num = numeradorNum->num;
        insereElemento(numeradorParcial, clone);
        // imprimeBignum(numeradorParcial->ultimo);
        // printf("  ");
        numeradorNum = numeradorNum->anterior;
        free(clone);
    }

    imprimeBignum(numeradorParcial->ultimo);
    printf(" - first\n\n");
    // system("pause");
    //   printf("%d", numeradorParcial->ultimo->num);
    //   printf("%d", numeradorParcial->primeiro->num);
    // system("pause");

    // printf("A");
    for (i = 0; i < 10; i++)
    {
        multiplicador->casas = intToBignum(i, multiplicador);
        multiplicar(divisor, multiplicador, guess);
        if (compara(guess, numeradorParcial) == 1)
        {
            printf("Quocient= %d  ", i);
            imprimeBignum(guess->ultimo);
            printf(" > ");
            imprimeBignum(numeradorParcial->ultimo);
            break;
        }
        destruir(multiplicador->primeiro);
        destruir(guess->primeiro);
    }
    printf("B");

    multi = i - 1;
    destruir(multiplicador->primeiro);
    destruir(guess->primeiro);
    printf("C");

    BigNum *aux = (BigNum *)malloc(sizeof(BigNum));
    aux = criar();
    aux->num = multi;
    printf("D");
    resultController->casas = 0;
    insereElemento(resultController, aux);
    printf("E");
    printf("\n");
    imprimeBignum(divisor->ultimo);
    printf("\n");
    imprimeBignum(resultController->ultimo);
    printf("\n");
    multiplicar(divisor, resultController, guess);
    // printf("F");
    //  printf("\n");
    printf("\n");
    imprimeBignum(guess->ultimo);
    printf("\n");
    system("pause");
    subtrair(numeradorParcial, guess, resto);
    printf("G");

    int count = 0;

    while (numeradorNum != NULL)
    {
        clone->num = numeradorNum->num;
        insereElemento(resto, clone);

        for (i = 0; i < 10; i++)
        {
            multiplicador->casas = intToBignum(i, multiplicador);
            multiplicar(divisor, multiplicador, guess);
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

        BigNum *aux = (BigNum *)malloc(sizeof(BigNum));
        aux = criar();
        aux->num = multi;

        insereElemento(resultController, aux);
        multiplicar(divisor, multiplicador, guess);
        subtrair(resto, guess, resto);

        numeradorNum = numeradorNum->anterior;
    }
    printf("H");
}

void fatorial(Lista *num, Lista *numClone, Lista *result) //*Fatorial OK!
{
    BigNum *res = (BigNum *)malloc(sizeof(BigNum));
    BigNum *um = (BigNum *)malloc(sizeof(BigNum));
    BigNum *aux = (BigNum *)malloc(sizeof(BigNum));
    Lista *controllerUm = (Lista *)malloc(sizeof(Lista));
    Lista *controllerAux = (Lista *)malloc(sizeof(Lista));
    Lista *parcialResult = (Lista *)malloc(sizeof(Lista));
    int end = 0;

    res = criar();
    res->num = 1;
    um = criar();
    um->num = 1;

    controllerUm->primeiro = um;
    controllerUm->ultimo = um;
    controllerUm->casas = 1;
    controllerAux->casas = 1;

    result->primeiro = res;

    subtrair(num, controllerUm, controllerAux);
    multiplicar(controllerAux, numClone, result);
    clone(result, parcialResult);
    // printf(" = ");
    // imprimeBignum(result->ultimo);
    // printf("\n");
    while (end != 1)
    {
        subtrair(controllerAux, controllerUm, controllerAux);

        // printf("ControllerAux: ");
        // imprimeBignum(controllerAux->ultimo);
        // printf("\n");
        if (controllerAux->primeiro->num == 0 && controllerAux->primeiro == controllerAux->ultimo)
        {
            end = 1;
        }
        else
        {
            multiplicar(controllerAux, parcialResult, result);
            clone(result, parcialResult);
            // printf(" = ");
            // imprimeBignum(result->ultimo);
            // printf("\n");
        }
    }

    destruir(controllerAux->primeiro);
    destruir(controllerUm->primeiro);
}
