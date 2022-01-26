#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *prox;
    struct nodo *ant;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

void lista_eliminar(lista_t *lista, int dato) {

    nodo_t *n_actual = lista->prim;

    while (n_actual != NULL) {

        if (n_actual->dato == dato) {

            if (n_actual->ant == NULL) {         // Si es el primero (no tiene nodo anterior)
                lista->prim = n_actual->prox;    // Cambio el primero por el siguiente
                if (lista->prim != NULL)         // Si no es el ultimo (verifico que no sea NULL, o sea que no sea el ultimo)
                    lista->prim->ant = NULL;     // El nuevo primero no tiene anterior

            }

            else {
                n_actual->ant->prox = n_actual->prox;       // Cambio el anterior por el siguiente
                if (n_actual->prox != NULL)                 // Si no es el ultimo (verifico que no sea NULL, o sea que no sea el ultimo)
                    n_actual->prox->ant = n_actual->ant;    // El nuevo siguiente no tiene anterior
            }

            free(n_actual);
            return;
        }

        n_actual = n_actual->prox;
    }
}

void imprimir_lista(lista_t *lista) {

    nodo_t *n_actual = lista->prim;

    while (n_actual != NULL) {
        printf("%d\n", n_actual->dato);
        n_actual = n_actual->prox;
    }
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

    imprimir_lista(&a);

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

// 29 min