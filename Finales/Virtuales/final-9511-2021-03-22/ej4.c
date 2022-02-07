#include <assert.h>
#include <stdio.h>

typedef struct nodo {
    int dato;
    struct nodo *prox;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

// HACER: escribir la implementacion:
void lista_mapear(lista_t *lista, int (*f)(int dato)) {

    if (lista == NULL || lista->prim == NULL || f == NULL)
        return;

    nodo_t *nodo_act = lista->prim;

    while(nodo_act != NULL){
        nodo_act->dato = f(nodo_act->dato);
        nodo_act = nodo_act->prox;
    }

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

    lista_t lista_vacia = {.prim = NULL};
    lista_mapear(&lista_vacia, duplicar);

    nodo_t n0_vacia = {.dato = 3, .prox = NULL};
    lista_t lista_un_nodo = {.prim = &n0_vacia};
    lista_mapear(&lista_un_nodo, duplicar);
    assert(lista_un_nodo.prim->dato == 3 * 2);

    printf("%s: OK\n", __FILE__);
    return 0;
}

//4 min
