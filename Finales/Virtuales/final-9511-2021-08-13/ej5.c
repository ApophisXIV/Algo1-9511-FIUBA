#include <stdio.h>
#include <assert.h>

typedef struct nodo {
    int dato;
    struct nodo *prox;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

int lista_buscar(lista_t *lista, int dato) {
    // HACER: implementar la funcion
}

int main(void) {
    // [3] -> [5] -> [3] -> [11]
    nodo_t n3 = {.dato = 11, .prox = NULL};
    nodo_t n2 = {.dato = 3, .prox = &n3};
    nodo_t n1 = {.dato = 5, .prox = &n2};
    nodo_t n0 = {.dato = 3, .prox = &n1};
    lista_t lista = {.prim = &n0};

    assert(lista_buscar(&lista, 3) == 0);
    assert(lista_buscar(&lista, 5) == 1);
    assert(lista_buscar(&lista, 11) == 3);
    assert(lista_buscar(&lista, 8) == -1);

    // OPCIONAL: escribir pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}

