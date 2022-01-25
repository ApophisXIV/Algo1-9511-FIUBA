#include <stdio.h>
#include <assert.h>

typedef struct nodo {
    int dato;
    struct nodo *izq;
    struct nodo *der;
} nodo_t;

int arbol_recorrer(nodo_t *nodo, const char *camino) {
    // HACER: implementar la funcion
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

    printf("%s: OK\n", __FILE__);
    return 0;
}
