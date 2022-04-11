typedef struct elemento *Lista;

Lista *criar();
Lista *somar(Elem *bigNumA, Elem *bigNumB);
Lista *subtrair(Elem *bigNumA, Elem *bigNumB);
Lista *multiplicar(Lista *bigNumA, Lista *bigNumB);
Lista *dividir(Lista *numerador, Lista *divisor);
Lista *intToBignum(int num);
void destruir(Lista *bigNum);
void imprimir(Lista *bigNum);
