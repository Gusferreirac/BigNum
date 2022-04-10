typedef struct elemento *Lista;

Lista *criar();
Lista *somar(Lista *bigNumA, Lista *bigNumB);
Lista *subtrair(Lista *bigNumA, Lista *bigNumB);
Lista *multiplicar(Lista *bigNumA, Lista *bigNumB);
Lista *dividir(Lista *numerador, Lista *divisor);
void destruir(Lista *bigNum);
void imprimir(Lista *bigNum);
void intToBignum(Lista *bigNum, int num);
