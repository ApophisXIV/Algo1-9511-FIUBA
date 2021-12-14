/**
 * @file main.c
 * @author Rodriguez Guido Ezequiel (guerodriguez@fi.uba.ar)
 * @Note Padron 108723
 * @version 1.0
 * @date 2021-12-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_EJERCICIO 1

#if N_EJERCICIO == 1
// (d) 1 2 6        (o) 3 7 9
// (d) 1 2 3 6 7 9  (o) -

/* -------------------------------- TDA Nodo -------------------------------- */

struct nodo {
	struct nodo *nodo_sig;
	int dato;
};
typedef struct nodo nodo_t;

// Constructor Nodo
nodo_t *nodo_constructor(int dato) {

	nodo_t *nodo = malloc(sizeof(struct nodo));
	if (nodo == NULL)
		return NULL;

	nodo->dato = dato;
	nodo->nodo_sig = NULL;

	return nodo;
}

// Destructor Nodo
void nodo_destructor(nodo_t *nodo) {
	free(nodo);
}

/* -------------------------------- TDA Lista ------------------------------- */

typedef struct {
	nodo_t *nodo_base;
} lista_t;

// Constructor Lista
lista_t *lista_constructor() {

	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL)
		return NULL;

	lista->nodo_base = NULL;

	return lista;
}

// Destructor Lista
void lista_destructor(lista_t *lista) {
	nodo_t *nodo_aux;
	while (lista->nodo_base != NULL) {
		nodo_aux = lista->nodo_base;
		lista->nodo_base = lista->nodo_base->nodo_sig;
		nodo_destructor(nodo_aux);
	}
	free(lista);
}

// Agregar nodo a lista
bool lista_nodo_insertar(nodo_t *nodo_pre, nodo_t *nodo_post, int dato) {
	nodo_t *nodo_ins = nodo_constructor(dato);
	if (nodo_ins == NULL)
		return NULL;

	nodo_ins->nodo_sig = nodo_post;
	nodo_pre->nodo_sig = nodo_ins;
	return true;
}

// Imprimir lista
void lista_imprimir(lista_t *lista) {
	nodo_t *nodo_aux = lista->nodo_base;
	while (nodo_aux != NULL) {
		printf("%d ", nodo_aux->dato);
		nodo_aux = nodo_aux->nodo_sig;
	}
	printf("\n");
}

bool nodo_agregar(lista_t *lista, int dato) {
	nodo_t *nodo_aux = lista->nodo_base;
	// Si la lista esta vacia
	if (nodo_aux == NULL) {
		lista->nodo_base = nodo_constructor(dato);
		return true;
	}
	// Si la lista tiene un solo nodo
	while (nodo_aux->nodo_sig != NULL) {
		nodo_aux = nodo_aux->nodo_sig;
	}
	// Agregar el nodo al final
	nodo_aux->nodo_sig = nodo_constructor(dato);
	return true;
}

/* -------------------------------------------------------------------------- */

void unir_listas_ordenadas(lista_t *d, lista_t *o) {
	nodo_t *nodo_d_actual = d->nodo_base;
	nodo_t *nodo_o_actual = o->nodo_base;
	nodo_t *nodo_aux;

	// Caso lista d u o vacia
	if (nodo_d_actual == NULL || nodo_o_actual == NULL) {
		nodo_d_actual = nodo_o_actual;	  // Le concateno la lista o a d que esta vacia
		nodo_o_actual = NULL;			  // Vacio la lista o
		return;
	}

	// Recorrer las listas hasta que una de ellas llegue a NULL
	while (nodo_d_actual != NULL && nodo_o_actual != NULL) {

		// Si el dato del nodo actual de la lista d es menor al de la lista o
		// avanzo hasta el siguiente nodo
		if (nodo_d_actual->dato < nodo_o_actual->dato) {

			// Busco el nodo siguiente de d que sea mayor que el nodo actual de o
			// Es decir, busco donde poder insertar el nodo actual de o en d
			while (nodo_d_actual->nodo_sig != NULL && nodo_d_actual->nodo_sig->dato <= nodo_o_actual->dato) {
				nodo_d_actual = nodo_d_actual->nodo_sig;
			}

			nodo_aux = nodo_o_actual->nodo_sig;					  // Guardo el nodo siguiente de o para backupearlo y despues reconectarlo a la lista o
			nodo_o_actual->nodo_sig = nodo_d_actual->nodo_sig;	  // El siguiente nodo de o se conecta al siguiente nodo
																  // de d (Me acoplo al nodo siguiente de d)
																  // [1 -> 2 -> 6]
																  // [     3 -> 6]
			nodo_d_actual->nodo_sig = nodo_o_actual;	// Suelto el nodo siguiente de d (Me acoplo al nodo actual de o) [1 -> 2 -> 3 -> 6]
			nodo_o_actual = nodo_aux;
		}

		else {

			nodo_aux = nodo_o_actual->nodo_sig;	   // Guardo el nodo siguiente de o para backupearlo y despues reconectarlo a la lista o

			// nodo_o_actual->nodo_sig = nodo_d_actual->nodo_sig;	  // 3 -> 6
			// nodo_d_actual->nodo_sig = nodo_o_actual;			  // 2 -> 3

			// nodo_o_actual = nodo_aux;	 // Reconecto el nodo siguiente de o a la lista o  [o -> 5]


			nodo_o_actual->nodo_sig = nodo_d_actual;

			d->nodo_base = nodo_o_actual;
			nodo_d_actual = d->nodo_base;

			nodo_o_actual = nodo_aux;
		}
	}

	while (nodo_o_actual != NULL) {
		nodo_d_actual->nodo_sig = nodo_o_actual;
		nodo_o_actual = nodo_o_actual->nodo_sig;
	}
}

void _unir_listas_ordenadas(lista_t *d, lista_t *o) {
	nodo_t *actual_d = d->nodo_base;
	nodo_t *actual_o = o->nodo_base;
	if (actual_o == NULL)
		return;

	while (actual_d != NULL && actual_o != NULL) {
		// lista_imnodo_baseir(d);
		// lista_imnodo_baseir(o);

		if (actual_d->dato > actual_o->dato) {
			nodo_t *aux = actual_o->nodo_sig;
			actual_o->nodo_sig = actual_d;

			d->nodo_base = actual_o;
			actual_d = d->nodo_base;

			actual_o = aux;
			// assert(0);
		}

		else if (actual_d->dato < actual_o->dato) {
			while (actual_d->nodo_sig != NULL && actual_d->nodo_sig->dato < actual_o->dato) {
				actual_d = actual_d->nodo_sig;
			}
			nodo_t *aux = actual_o->nodo_sig;
			actual_o->nodo_sig = actual_d->nodo_sig;
			actual_d->nodo_sig = actual_o;
			// assert(0);
			actual_o = aux;
			// lista_imprimir(d);
		}
	}
	while (actual_o != NULL) {
		actual_d->nodo_sig = actual_o;
		actual_o = actual_o->nodo_sig;
	}
}

int main(void) {

	lista_t *l_d = lista_constructor();
	lista_t *l_o = lista_constructor();

	// (d) 1 2 6            (o) 3 5 7 9
	// (d) 1 2 3 6          (o) 5 7 9

	nodo_agregar(l_d, 4);
	nodo_agregar(l_d, 5);
	nodo_agregar(l_d, 10);

	nodo_agregar(l_o, 3);
	nodo_agregar(l_o, 5);
	nodo_agregar(l_o, 7);
	nodo_agregar(l_o, 9);

	unir_listas_ordenadas(l_d, l_o);

	lista_imprimir(l_d);
	lista_imprimir(l_o);

	//------------------------------------

	lista_t *_l_d = lista_constructor();
	lista_t *_l_o = lista_constructor();

	// (d) 1 2 6            (o) 3 5 7 9
	// (d) 1 2 3 6          (o) 5 7 9

	nodo_agregar(_l_d, 4);
	nodo_agregar(_l_d, 5);
	nodo_agregar(_l_d, 10);

	nodo_agregar(_l_o, 3);
	nodo_agregar(_l_o, 5);
	nodo_agregar(_l_o, 7);
	nodo_agregar(_l_o, 9);

	_unir_listas_ordenadas(_l_d, _l_o);

	lista_imprimir(_l_d);
	lista_imprimir(_l_o);

	return 0;
}

#elif N_EJERCICIO == 2

int main(void) {

	return 0;
}

#elif N_EJERCICIO == 3


int main(void) {

	return 0;
}

#endif