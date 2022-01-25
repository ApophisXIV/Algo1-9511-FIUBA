#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef struct nodo {
    int dato;
    struct nodo *prox;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

bool hay_ciclo(lista_t *lista) {
    // HACER: implementar la funcion
}

int main(void) {
    // creamos "a mano" la lista: 10 -> 20 -> 30 -> 40
    nodo_t n0, n1, n2, n3;
    n0 = (nodo_t){.dato = 10, .prox = &n1};
    n1 = (nodo_t){.dato = 20, .prox = &n2};
    n2 = (nodo_t){.dato = 30, .prox = &n3};
    n3 = (nodo_t){.dato = 40, .prox = NULL};

    lista_t a = {.prim = &n0};

    assert(!hay_ciclo(&a));

    n3.prox = &n1;

    assert(hay_ciclo(&a));

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
