typedef struct bigNum
{
    struct bigNum *proximo;
    struct bigNum *anterior;
    struct bigNum *ultimo;
    int num;
} BigNum;

typedef struct lista
{
    struct bigNum *primeiro;
    struct bigNum *ultimo;
} Lista;

BigNum *criar();
void somar(BigNum *bigNumAHead, BigNum *bigNumBHead, BigNum **res, Lista *list);
BigNum *subtrair(BigNum *bigNumA, BigNum *bigNumB);
BigNum *multiplicar(BigNum *bigNumA, BigNum *bigNumB);
BigNum *dividir(BigNum *numerador, BigNum *divisor);
void *intToBignum(int num, BigNum **head, Lista *list);
void destruir(BigNum *bigNum);
void imprimir(BigNum *bigNum);
void imprimeBignum(BigNum *Num);
