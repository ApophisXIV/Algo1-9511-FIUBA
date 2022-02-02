#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct nodo {
    int dato;
    struct nodo *prox;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

// HACER: escribir la implementacion, en forma RECURSIVA. (Puede ser necesario
// agregar una funcion privada).

bool esta_ordenada(lista_t *lista) {

    if (lista == NULL || lista->prim == NULL)
        return false;

    nodo_t *nodo_act = lista->prim;
    nodo_t *nodo_sig = nodo_act->prox;

    if (nodo_sig == NULL)
        return true;

    if (nodo_act->dato < nodo_sig->dato){
        lista_t lista_nueva = {.prim = nodo_sig};
        return esta_ordenada(&lista_nueva);
    }

    return false;
}

int main(void) {
    // [3] -> [5] -> [8] -> [11]
    nodo_t n3 = {.dato = 11, .prox = NULL};
    nodo_t n2 = {.dato = 8, .prox = &n3};
    nodo_t n1 = {.dato = 5, .prox = &n2};
    nodo_t n0 = {.dato = 3, .prox = &n1};
    lista_t lista = {.prim = &n0};

    assert(esta_ordenada(&lista));

    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - Repetir la prueba con una lista desordenada, y verificar que la
    //   funcion devuelve false
    // - Repetir la prueba con una lista vacia (es indistinto lo que devuelve
    //   la funcion, pero no deberia fallar)

    printf("%s: OK\n", __FILE__);
    return 0;
}

//9 min