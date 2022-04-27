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
    int casas;
    struct bigNum *ultimo;
} Lista;

BigNum *criar();
void somar(BigNum *bigNumAHead, BigNum *bigNumBHead, BigNum **res, Lista *list);
void subtrair(Lista *bigNumAHead, Lista *bigNumBHead, BigNum **res, Lista *list);
void multiplicar(Lista *bigNumAHead, Lista *bigNumBHead, BigNum **res, Lista *list);
void dividir(Lista *numerador, Lista *divisor, Lista *resultController);
void fatorial(Lista *num, Lista *result);
int *intToBignum(int num, BigNum **head, Lista *list);
void destruir(BigNum *bigNum);
void imprimir(BigNum *bigNum);
void imprimeBignum(BigNum *Num);
void removerZeros(BigNum *bigNum, Lista *controller);
