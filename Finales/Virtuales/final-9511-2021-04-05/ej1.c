#include <assert.h>
#include <stdio.h>

typedef struct nodo {
    int dato;
    struct nodo *izq;
    struct nodo *der;
} nodo_t;

// el dato en cada nodo es
// mayor o igual que el dato de cualquier nodo del sub-árbol izquierdo, y menor o igual que el
// dato de cualquier nodo del sub-árbol derecho.

nodo_t *abb_buscar(nodo_t *nodo, int dato) {

    if (nodo == NULL)
        return NULL;

    if (dato == nodo->dato)
        return nodo;

    if (dato < nodo->dato)
        return abb_buscar(nodo->izq, dato);
    return abb_buscar(nodo->der, dato);
}

int main(void) {
    // el arbol ejemplo del enunciado
    nodo_t n1 = {.dato = 1};
    nodo_t n4 = {.dato = 4};
    nodo_t n7 = {.dato = 7};
    nodo_t n13 = {.dato = 13};
    nodo_t n14 = {.dato = 14, .izq = &n13};
    nodo_t n10 = {.dato = 10, .der = &n14};
    nodo_t n6 = {.dato = 6, .izq = &n4, .der = &n7};
    nodo_t n3 = {.dato = 3, .izq = &n1, .der = &n6};
    nodo_t raiz = {.dato = 8, .izq = &n3, .der = &n10};

    nodo_t *n = abb_buscar(&raiz, 6);
    assert(n == &n6);

    // OPCIONAL: agregar mas casos de prueba
    // Nodo no existente
    n = abb_buscar(&raiz, 15);
    assert(n == NULL);

    printf("%s: OK\n", __FILE__);
    return 0;
}

//11 min
