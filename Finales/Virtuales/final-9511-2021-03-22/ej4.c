#include <stdio.h>
#include <assert.h>

typedef struct nodo {
    int dato;
    struct nodo *prox;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

// HACER: escribir la implementacion:
void lista_mapear(lista_t *lista, int (*f)(int dato)) {
}

static int duplicar(int n) {
    return n * 2;
}

int main(void) {
    // [3] -> [5] -> [8] -> [11]
    nodo_t n3 = {.dato = 11, .prox = NULL};
    nodo_t n2 = {.dato = 8, .prox = &n3};
    nodo_t n1 = {.dato = 5, .prox = &n2};
    nodo_t n0 = {.dato = 3, .prox = &n1};
    lista_t lista = {.prim = &n0};

    lista_mapear(&lista, duplicar);
    assert(lista.prim->dato == 3 * 2);
    assert(lista.prim->prox->dato == 5 * 2);
    assert(lista.prim->prox->prox->dato == 8 * 2);
    assert(lista.prim->prox->prox->prox->dato == 11 * 2);

    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - Lista vacía
    // - Lista con un nodo

    printf("%s: OK\n", __FILE__);
    return 0;
}

