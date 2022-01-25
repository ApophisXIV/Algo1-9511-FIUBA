#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct nodo {
    int dato;
    struct nodo *prox;
    struct nodo *ant;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

void lista_eliminar(lista_t *lista, int dato) {
    // HACER: implementar la funcion
}

int main(void) {
    // creamos "a mano" la lista: 10 <-> 20 <-> 30 <-> 40
    nodo_t *n0 = malloc(sizeof(nodo_t));
    nodo_t *n1 = malloc(sizeof(nodo_t));
    nodo_t *n2 = malloc(sizeof(nodo_t));
    nodo_t *n3 = malloc(sizeof(nodo_t));
    *n0 = (nodo_t){.dato = 10, .prox = n1, .ant = NULL};
    *n1 = (nodo_t){.dato = 20, .prox = n2, .ant = n0};
    *n2 = (nodo_t){.dato = 30, .prox = n3, .ant = n1};
    *n3 = (nodo_t){.dato = 40, .prox = NULL, .ant = n2};

    lista_t a = {.prim = n0};

    lista_eliminar(&a, 30);

    assert(a.prim->dato == 10);
    assert(a.prim->prox->dato == 20);
    assert(a.prim->prox->prox->dato == 40);
    assert(a.prim->prox->prox->ant->dato == 20);

    free(n0);
    free(n1);
    // n2 ya deberia haber sido liberado
    free(n3);

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}


