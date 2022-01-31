#include <assert.h>
#include <stdio.h>

typedef struct nodo {
    int dato;
    struct nodo *izq;
    struct nodo *der;
} nodo_t;

int _arbol_recorrer(nodo_t *nodo, const char *camino) {

    if (nodo == NULL)    // Si el nodo es nulo, no hay nada que recorrer
        return 0;

    if (*camino == '0')
        return _arbol_recorrer(nodo->izq, camino + 1);    // Izquierda

    if (*camino == '1')
        return _arbol_recorrer(nodo->der, camino + 1);    // Derecha

    return nodo->dato;
}

int arbol_recorrer(nodo_t *nodo, const char *camino) {
    if (nodo == NULL || camino == NULL || *camino == '\0')
        return 0;
    return _arbol_recorrer(nodo, camino);
}

int main(void) {
    // el arbol ejemplo del enunciado
    nodo_t n4 = {.dato = 4};
    nodo_t n9 = {.dato = 9, .izq = &n4};
    nodo_t n5d = {.dato = 5, .der = &n9};
    nodo_t n5i = {.dato = 5};
    nodo_t n11 = {.dato = 11};
    nodo_t n6 = {.dato = 6, .izq = &n5i, .der = &n11};
    nodo_t n2 = {.dato = 2};
    nodo_t n7 = {.dato = 7, .izq = &n2, .der = &n6};
    nodo_t raiz = {.dato = 2, .izq = &n7, .der = &n5d};

    assert(arbol_recorrer(&raiz, "010") == 5);

    // OPCIONAL: escribir casos de prueba adicionales

    assert(arbol_recorrer(&raiz, "000011") == 0);

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 13 min



