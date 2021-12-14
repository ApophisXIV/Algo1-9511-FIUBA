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

//TODO 
#if N_EJERCICIO == 1

struct nodo {
	struct nodo *sig;
	int dato;
};
typedef struct nodo nodo_t;

typedef struct {
	nodo_t *prim;
} lista_t;

lista_t *lista_crear() {
	lista_t *l = malloc(sizeof(lista_t *));
	if (l == NULL) {
		return NULL;
	}
	return l;
}

void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra) {

	nodo_t *act = l->prim;
	while (act != NULL) {
		if (!visitar(act->dato, extra))
			return;

		act = act->sig;
	}
}

void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b)) {
	nodo_t *act = l->prim;
	nodo_t *anterior = NULL;

	while (act != NULL && cmp(act->dato, dato) != 0) {
		anterior = act;
		act = act->sig;
	}

	if (act == NULL) {
		return NULL;
	}
	if (anterior == NULL)
		l->prim = act->sig;
	else
		anterior->sig = act->sig;

	void *aux = act->dato;
	free(act);
	return aux;
}

bool lista_insertar_al_final(lista_t *l, void *dato) {

	nodo_t *act = l->prim;
	nodo_t *n = malloc(sizeof(nodo_t *));
	if (n == NULL) {
		return false;
	}
	while ((act->sig) != NULL) {
		act = act->sig;
	}

	act->sig = n;
	n->sig = NULL;
	n->dato = dato;
	return true;
}

// Versión "manual":
lista_t *lista_filtrar_1(lista_t *l, bool (*f)(void *)) {
	lista_t *lista_filtrados = lista_crear();
	if (lista_filtrados == NULL)
		return NULL;

	nodo_t *final = NULL;

	while (l->prim != NULL && f(l->prim->dato)) {
		nodo_t *actual = l->prim;
		l->prim = actual->sig;

		actual->sig = NULL;

		if (lista_filtrados->prim == NULL)
			lista_filtrados->prim = actual;
		else
			final->sig = actual;
		final = actual;
	}

	if (l->prim == NULL)
		return lista_filtrados;

	nodo_t *anterior = l->prim;
	while (anterior->sig != NULL) {
		nodo_t *actual = anterior->sig;
		if (f(actual->dato)) {
			anterior->sig = actual->sig;

			/* Si quisieramos insertar al comienzo:
			actual->sig = lista_filtrados->prim;
			lista_filtrados->prim = actual;*/

			actual->sig = NULL;

			if (lista_filtrados->prim == NULL)
				lista_filtrados->prim = actual;
			else
				final->sig = actual;
			final = actual;
		} else
			anterior = actual;
	}

	return lista_filtrados;
}

// Versión punteros dobles:
lista_t *lista_filtrar_2(lista_t *l, bool (*f)(void *)) {
	lista_t *lista_filtrados = lista_crear();
	if (lista_filtrados == NULL)
		return NULL;

	nodo_t **plo = &l->prim;
	nodo_t **plf = &lista_filtrados->prim;

	while ((*plo) != NULL) {
		nodo_t *actual = *plo;
		if (f(actual->dato)) {
			*plo = actual->sig;
			actual->sig = NULL;
			*plf = actual;
			plf = &actual->sig;
		} else
			plo = &actual->sig;
	}

	return lista_filtrados;
}

bool mide_menos_de_5(void *s) {
	return strlen(s) < 5;
}

bool imprimir(void *s, void *e) {
	printf("%s, ", (char *)s);
	return true;
}

int main(void) {

	lista_t *l = lista_crear();
	lista_insertar_al_final(l, "nos");
	lista_insertar_al_final(l, "encanta");
	lista_insertar_al_final(l, "programar");
	lista_insertar_al_final(l, "para");
	lista_insertar_al_final(l, "algoritmos");
	lista_insertar_al_final(l, "y");
	lista_insertar_al_final(l, "programacion");

	printf("LISTA ORIGINAL:\n");
	lista_recorrer(l, imprimir, NULL);
	putchar('\n');

	lista_t *lf = lista_filtrar_1(l, mide_menos_de_5);
	printf("LISTA DE strlen >= 5:\n");
	lista_recorrer(l, imprimir, NULL);
	putchar('\n');

	printf("LISTA DE strlen < 5:\n");
	lista_recorrer(lf, imprimir, NULL);
	putchar('\n');

	// lista_destruir(l, NULL);
	// lista_destruir(lf, NULL);

	return 0;
}

#elif N_EJERCICIO == 2

int *detectar_duplicados(const int pc[], size_t n_pc, const int lh[], size_t n_lh, size_t *n_dup) {

	int *duplicados = malloc((n_pc < n_lh ? n_pc : n_lh) * sizeof(int));
	*n_dup = 0;

	size_t epc = 0, elh = 0;

	while (epc < n_pc && elh < n_lh) {
		if (pc[epc] < lh[elh])
			epc++;
		else if (lh[elh] < pc[epc])
			elh++;
		else {
			duplicados[(*n_dup)++] = pc[epc++];
			elh++;
		}
	}

	return duplicados;
}

int main(void) {

	return 0;
}

#elif N_EJERCICIO == 3

// Sacando un elemento:
float sumar_elementos_1(const float v[], size_t n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return v[0];

	// return sumar_elementos(v, n - 1) + v[n-1];
	return sumar_elementos_1(v + 1, n - 1) + v[0];
}

// División y conquista:
float sumar_elementos_2(const float v[], size_t n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return v[0];

	size_t mitad = n / 2;
	return sumar_elementos_2(v, mitad) + sumar_elementos_2(v + mitad, n - mitad);
}

int main(void) {

	return 0;
}

#endif