typedef struct bigNum
{
    struct bigNum *proximo;
    struct bigNum *anterior;
    int num;
} BigNum;

typedef struct lista
{
    struct bigNum *primeiro;
    int casas;
    struct bigNum *ultimo;
} Lista;

BigNum *criar();
void somar(BigNum *bigNumAHead, BigNum *bigNumBHead, Lista *list);
void subtrair(Lista *bigNumAHead, Lista *bigNumBHead, Lista *list);
void multiplicar(Lista *bigNumAHead, Lista *bigNumBHead, Lista *list);
void dividir(Lista *numerador, Lista *divisor, Lista *resultController);
void fatorial(Lista *num, Lista *numClone, Lista *result);
void clone(Lista *a, Lista *b);
int intToBignum(int num, Lista *list);
int contaCasas(Lista *li);
void incrementa(Lista *li);
void insereElemento(Lista *controller, BigNum *num);
int compara(Lista *a, Lista *b);
void destruir(BigNum *bigNum);
void imprimir(BigNum *bigNum);
void imprimeBignum(BigNum *Num);
void removerZeros(BigNum *bigNum, Lista *controller);
void digit_shift(BigNum *n, int d);
