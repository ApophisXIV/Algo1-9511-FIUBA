#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	int dato;
	struct nodo *prox;
} nodo_t;

typedef struct {
	nodo_t *prim;
} lista_t;

void lista_destruir(lista_t *lista) {
	nodo_t *n = lista->prim;
	while (n) {
		nodo_t *next = n->prox;
		free(n);
		n = next;
	}
	free(lista);
}

bool lista_repetir(lista_t *lista) {

	if (lista == NULL || lista->prim == NULL)
		return false;

	lista_t *l_aux = malloc(sizeof(lista_t));
	if (l_aux == NULL)
		return false;
	l_aux->prim = NULL;

	nodo_t *n_act = lista->prim;
	nodo_t *ult_nodo_aux = NULL;

	while (n_act != NULL) {

		nodo_t *n_aux = malloc(sizeof(nodo_t));
		if (n_aux == NULL) {
			lista_destruir(l_aux);
			return false;
		}

		n_aux->dato = n_act->dato;
		n_aux->prox = NULL;

		if (ult_nodo_aux != NULL)
			ult_nodo_aux->prox = n_aux;
		else
			l_aux->prim = n_aux;

		ult_nodo_aux = n_aux;

		if (n_act->prox == NULL) {
			n_act->prox = l_aux->prim;	  // n_act conserva el ultimo elemento de la lista original
										  // Concateno las listas
			break;
		}

		n_act = n_act->prox;
	}

	return true;
}

int main(void) {
	// creamos "a mano" la lista: 10 -> 20 -> 30 -> 40
	nodo_t *n0 = malloc(sizeof(nodo_t));
	nodo_t *n1 = malloc(sizeof(nodo_t));
	nodo_t *n2 = malloc(sizeof(nodo_t));
	nodo_t *n3 = malloc(sizeof(nodo_t));
	*n0 = (nodo_t){.dato = 10, .prox = n1};
	*n1 = (nodo_t){.dato = 20, .prox = n2};
	*n2 = (nodo_t){.dato = 30, .prox = n3};
	*n3 = (nodo_t){.dato = 40, .prox = NULL};
	lista_t *a = malloc(sizeof(lista_t));
	a->prim = n0;

	lista_repetir(a);

	assert(a->prim->dato == 10);
	assert(a->prim->prox->dato == 20);
	assert(a->prim->prox->prox->dato == 30);
	assert(a->prim->prox->prox->prox->dato == 40);
	assert(a->prim->prox->prox->prox->prox->dato == 10);
	assert(a->prim->prox->prox->prox->prox->prox->dato == 20);
	assert(a->prim->prox->prox->prox->prox->prox->prox->dato == 30);
	assert(a->prim->prox->prox->prox->prox->prox->prox->prox->dato == 40);
	assert(a->prim->prox->prox->prox->prox->prox->prox->prox->prox == NULL);

	lista_destruir(a);

	// OPCIONAL: Pruebas adicionales

	printf("%s: OK\n", __FILE__);
	return 0;
}
