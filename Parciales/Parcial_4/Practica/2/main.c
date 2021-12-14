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

struct nodo {
	struct nodo *sig;
	int dato;
};

typedef struct {
	struct nodo *prim;
} lista_enteros_t;

// Versión 1: Manual.
void lista_enteros_borrar_1(lista_enteros_t *l, int e) {
	while (l->prim != NULL && l->prim->dato == e) {
		struct nodo *a_borrar = l->prim;
		l->prim = a_borrar->sig;
		free(a_borrar);
	}

	if (l->prim == NULL)
		return;

	struct nodo *anterior = l->prim;
	while (anterior->sig != NULL) {
		struct nodo *actual = anterior->sig;

		if (actual->dato == e) {
			anterior->sig = actual->sig;
			free(actual);
		} else
			anterior = actual;
	}
}

// Versión 2: Con punteros dobles.
void lista_enteros_borrar_2(lista_enteros_t *l, int e) {
	struct nodo **pactual = &l->prim;

	while ((*pactual) != NULL) {
		struct nodo *actual = *pactual;
		if (actual->dato == e) {
			*pactual = actual->sig;
			free(actual);
		} else
			pactual = &actual->sig;
	}
}

// Versión 3: Recursiva.
static struct nodo *_lista_enteros_borrar(struct nodo *n, int e) {
	if (n == NULL)
		return NULL;

	n->sig = _lista_enteros_borrar(n->sig, e);

	if (n->dato != e)
		return n;

	struct nodo *aux = n->sig;
	free(n);
	return aux;
}

void lista_enteros_borrar_3(lista_enteros_t *l, int e) {
	l->prim = _lista_enteros_borrar(l->prim, e);
}

#elif N_EJERCICIO == 2

int *consolidar_asistentes(const int dia1[], size_t n1, const int dia2[], size_t n2, size_t *n_asis) {
	int *asis = malloc((n1 + n2) * sizeof(int));
	if (asis == NULL)
		return NULL;

	*n_asis = 0;
	size_t e1 = 0, e2 = 0;

	while (e1 < n1 && e2 < n2) {
		if (dia1[e1] < dia2[e2])
			asis[(*n_asis)++] = dia1[e1++];
		else if (dia1[e1] > dia2[e2])
			asis[(*n_asis)++] = dia2[e2++];
		else {
			asis[(*n_asis)++] = dia1[e1++];
			e2++;
		}
	}

	while (e1 < n1)
		asis[(*n_asis)++] = dia1[e1++];
	while (e2 < n2)
		asis[(*n_asis)++] = dia2[e2++];

	return asis;
}

#elif N_EJERCICIO == 3

// Versión 1: Sacando de a uno.
bool esta_ordenado_1(const float v[], size_t n) {
	if (n < 2)
		return true;

	if (v[0] > v[1])
		return false;

	// return v[0] <= v[1] && esta_ordenado(v + 1, n - 1);
	return esta_ordenado_1(v + 1, n - 1);
}

// Versión 2: División y conquista (esta versión usa menos stack pero no es más eficiente que la 1).
bool esta_ordenado_2(const float v[], size_t n) {
	if (n < 2)
		return true;

	size_t n1 = n / 2;
	size_t n2 = n - n / 2;

	if (v[n1 - 1] > v[n1])
		return false;

	return esta_ordenado_2(v, n1) && esta_ordenado_2(v + n1, n2);
}

#endif