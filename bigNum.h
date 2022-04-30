#ifndef BIGNUM_H
#define BIGNUM_H

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
void clone(Lista *a, Lista *b);
int intToBignum(int num, Lista *list);
int contaCasas(Lista *li);
void incrementa(Lista *li);
void insereElemento(Lista *controller, BigNum *num);
int compara(Lista *a, Lista *b);
void destruir(BigNum *bigNum);
void imprimeBignum(BigNum *Num);
void removerZeros(BigNum *bigNum, Lista *controller);
void freeLista(Lista *li);
void freeNo(BigNum *no);

#endif