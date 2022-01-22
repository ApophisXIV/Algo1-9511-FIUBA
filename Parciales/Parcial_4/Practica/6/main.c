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

/*1. Teniendo un TDA lista enlazada genérica definido como
typedef struct {
struct nodo *prim;
} lista_t;
y su nodo como
struct nodo {
struct nodo *sig;
void *dato;
};
implementar una primitiva
bool lista_esta_ordenada(const lista_t *l, int (*cmp)(const void *, const void *));
que indique si la lista está ordenada.*/

typedef struct {
	struct nodo *prim;
} lista_t;

struct nodo {
	struct nodo *sig;
	void *dato;
};

typedef struct nodo nodo_t;

nodo_t *nodo_crear(void *dato) {
	nodo_t *n = malloc(sizeof(nodo_t));
	if (n == NULL)
		return NULL;
	n->dato = dato;
	n->sig = NULL;
	return n;
}

void destruir_dato(void *dato) {
	free(dato);
}

void nodo_destruir(nodo_t *nodo, void (*destruir_dato)(void *dato)) {
	if (destruir_dato != NULL)
		destruir_dato(nodo->dato);
	free(nodo);
}

lista_t *lista_crear() {
	lista_t *l = malloc(sizeof(lista_t));
	if (l == NULL)
		return NULL;
	l->prim = NULL;
	return l;
}

void lista_destruir(lista_t *l) {
	nodo_t *n = l->prim;
	while (n != NULL) {
		nodo_t *aux = n;
		n = n->sig;
		free(aux);
	}
	free(l);
}

void lista_imprimir(lista_t *l) {
	nodo_t *nodo = l->prim;
	while (nodo != NULL) {
		printf("%s ", (char *)nodo->dato);
		nodo = nodo->sig;
	}
	putchar('\n');
}

bool lista_insertar_al_final(lista_t *l, void *dato) {
	nodo_t *nodo = nodo_crear(dato);
	if (nodo == NULL)
		return false;
	if (l->prim == NULL)
		l->prim = nodo;
	else {
		nodo_t *aux = l->prim;
		while (aux->sig != NULL)
			aux = aux->sig;
		aux->sig = nodo;
	}
	return true;
}

/* -------------------------------------------------------------------------- */

int comparar_primer_letra(const void *a, const void *b) {
	return *(char*)a - *(char*)b;
}

bool lista_esta_ordenada(const lista_t *l, int (*cmp)(const void *, const void *)) {
	nodo_t *nodo = l->prim;
	while (nodo != NULL && nodo->sig != NULL) {
		if (cmp(nodo->dato, nodo->sig->dato) > 0)
			return false;
		nodo = nodo->sig;
	}
	return true;
}

int main(void) {
	lista_t *l = lista_crear();

	lista_insertar_al_final(l, "a");
	lista_insertar_al_final(l, "b");
	lista_insertar_al_final(l, "c");
	lista_insertar_al_final(l, "d");
	lista_insertar_al_final(l, "z");
	lista_imprimir(l);

	printf("%s\n", lista_esta_ordenada(l, comparar_primer_letra) ? "SI" : "NO");

	lista_destruir(l);

	return 0;
}

#elif N_EJERCICIO == 2

// Producto actual
typedef struct {
	int codigo;
	char nombre[100];
	float precio;
	size_t stock;
} producto_t;

// Referencia de actualizacion
struct actualizacion {
	int codigo;
	float precio;
};

// Complejidad: O(n)
void remarcar_precios(producto_t *productos[], size_t nproductos, const struct actualizacion actualizaciones[], size_t nactualizaciones) {
	for (size_t j = 0, i = 0; j < nproductos; j++)
		if (productos[j]->codigo == actualizaciones[i].codigo)
			productos[j]->precio = actualizaciones[i++].precio;
}

int main(void) {

	producto_t productos_limpieza[] = {
		{1, "jabon", 10.5, 10},
		{2, "shampoo", 15.5, 4},
		{3, "servilletas", 19.9, 3},
		{4, "barbijos", 5.5, 20},
		{5, "dentifrico", 55.5, 2},
	};

	producto_t *productos[5];
	for (size_t i = 0; i < 5; i++) {
		productos[i] = &productos_limpieza[i];
	}

	struct actualizacion remarcados[] = {
		{1, 12.5},
		{3, 29.9},
		{4, 10.0},

	};

	size_t n_prods = sizeof(productos_limpieza) / sizeof(producto_t);
	size_t n_prods_act = sizeof(remarcados) / sizeof(struct actualizacion);

	remarcar_precios(productos, n_prods, remarcados, n_prods_act);

	for (size_t i = 0; i < n_prods; i++) {
		printf("%d %s %.2f %zu\n", productos_limpieza[i].codigo, productos_limpieza[i].nombre, productos_limpieza[i].precio, productos_limpieza[i].stock);
	}

	return 0;
}

#elif N_EJERCICIO == 3

unsigned int dividir_iterativo(unsigned int a, unsigned int b) {
	unsigned int q = 0;
	while (a >= b) {
		a -= b;
		q++;
	}
	return q;
}

unsigned int _dividir(unsigned int a, unsigned int b) {
	if (b > a)
		return 0;
	return 1 + _dividir(a - b, b);
}

unsigned int dividir(unsigned int a, unsigned int b) {
	if (a == 0 || b == 0 || b > a)
		return 0;
	return 1 + _dividir(a - b, b);
}

int main(void) {

	unsigned int res_1 = dividir(9, 1);

	printf("Res: %u\n", res_1);

	return 0;
}

#endif