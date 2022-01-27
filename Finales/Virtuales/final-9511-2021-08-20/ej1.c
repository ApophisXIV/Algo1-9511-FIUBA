#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct nodo {
    char dato;
    struct nodo *prox;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;


int m_strcmp(const char *s1, const char *s2) {
    while (*s1 == *s2) {
        if (*s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int lista_cmp(lista_t *a, lista_t *b) {

    if(a == NULL || b == NULL || a->prim == NULL || b->prim == NULL)
        return 0;

    nodo_t* a_actual = a->prim;
    nodo_t* b_actual = b->prim;

    while(a_actual->dato == b_actual->dato) {

        // Si son iguales (longitud y contenido)
        if(a_actual->prox == NULL && b_actual->prox == NULL)
            return 0;

        // Si una lista es mas corta que la otra
        // (Criterio de diseño: Si una lista es mas corta que la otra, se devuelve -1)
        if(a_actual->prox == NULL || b_actual->prox == NULL)
            return -1;

        a_actual = a_actual->prox;
        b_actual = b_actual->prox;
    }

    return a_actual->dato - b_actual->dato;
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
    
    nodo_t c2 = {.dato = 'a', .prox = NULL};
    nodo_t c1 = {.dato = 's', .prox = &c2};
    nodo_t c0 = {.dato = 'a', .prox = &c1};
    lista_t c = {.prim = &c0};

    nodo_t d3 = {.dato = 'r', .prox = NULL};
    nodo_t d2 = {.dato = 'a', .prox = &d3};
    nodo_t d1 = {.dato = 's', .prox = &d2};
    nodo_t d0 = {.dato = 'a', .prox = &d1};
    lista_t d = {.prim = &d0};

    assert(lista_cmp(&d, &c) < 0);


    printf("%s: OK\n", __FILE__);
    return 0;
}

// 7 min
