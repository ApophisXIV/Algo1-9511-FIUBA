#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	char dato;
	struct nodo *izq;
	struct nodo *der;
} nodo_t;

// HACER: implementar las funciones.
// Recomendacion: pensarlas en forma recursiva.
// Puede que sea necesario crear funciones auxiliares.

void arbol_destruir(nodo_t *nodo) {
    if (nodo == NULL)
        return;
    arbol_destruir(nodo->izq);
    arbol_destruir(nodo->der);
    free(nodo);
}

// abc...de..f..
/*
	a->izq = b
		b->izq = c
			c->izq = NULL
			c->der = NULL
		b->der = NULL
	a->der = d
		d->izq = e
			e->izq = NULL
			e->der = NULL
		d->der = f
			f->izq = NULL
			f->der = NULL

*/


size_t arbol_recorrer(nodo_t *nodo){
    if (nodo == NULL)
        return 1;
    return arbol_recorrer(nodo->izq) + arbol_recorrer(nodo->der) + 1;
}

nodo_t *arbol_crear(char s[]) {

	if (*s == '\0' || s == NULL || *s == '.')
		return NULL;

	nodo_t *nodo = malloc(sizeof(nodo_t));
	nodo->dato = *s;
	nodo->izq = arbol_crear(s + 1);
    nodo->der = arbol_crear(s + arbol_recorrer(nodo->izq) + 1);

	return nodo;
}

void print_abb(nodo_t *nodo) {
	if (nodo == NULL)
		return;

	if (nodo->izq == NULL && nodo->der == NULL) {
		fprintf(stderr, "[%c]", nodo->dato);
		return;
	}

	fprintf(stderr, "[%c]", nodo->dato);
	print_abb(nodo->izq);
	print_abb(nodo->der);
}

int main(void) {
	nodo_t *raiz = arbol_crear("abc...de..f..");

	/*
				 a   <--- raiz
			   /  \
			  b    d
			/     / \
		   c     e   f
	*/

	print_abb(raiz);

	assert(raiz->dato == 'a');
	assert(raiz->izq->dato == 'b');
	assert(raiz->der->dato == 'd');
	assert(raiz->izq->izq->dato == 'c');
	assert(raiz->der->izq->dato == 'e');
	assert(raiz->der->der->dato == 'f');

	// arbol_destruir(raiz);

	// OPCIONAL: escribir pruebas adicionales

	printf("%s: OK\n", __FILE__);
	return 0;
}
