#include <stdio.h>
#include <assert.h>

typedef struct nodo {
    char dato;
    struct nodo *prox;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

int lista_cmp(lista_t *a, lista_t *b) {
    // HACER: implementar la funcion
}

int main(void) {
    // lista a:  c -> a -> m -> a
    nodo_t a3 = {.dato = 'a', .prox = NULL};
    nodo_t a2 = {.dato = 'm', .prox = &a3};
    nodo_t a1 = {.dato = 'a', .prox = &a2};
    nodo_t a0 = {.dato = 'c', .prox = &a1};
    lista_t a = {.prim = &a0};

    // lista b:  c -> a -> s -> a
    nodo_t b3 = {.dato = 'a', .prox = NULL};
    nodo_t b2 = {.dato = 's', .prox = &b3};
    nodo_t b1 = {.dato = 'a', .prox = &b2};
    nodo_t b0 = {.dato = 'c', .prox = &b1};
    lista_t b = {.prim = &b0};

    assert(lista_cmp(&a, &b) < 0);
    assert(lista_cmp(&a, &a) == 0);
    assert(lista_cmp(&b, &a) > 0);

    // OPCIONAL: Pruebas adicionales. Sugerencia:
    // - Listas de diferente longitud: "asa" < "asar"

    printf("%s: OK\n", __FILE__);
    return 0;
}


