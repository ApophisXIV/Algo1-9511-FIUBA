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

/* -------------------------------- TDA Lista ------------------------------- */

/* -------------------------------------------------------------------------- */
// Invariante de representacion:
/* -------------------------------------------------------------------------- */
// El primer dato es el menor de la lista
// El ultimo dato es el mayor de la lista
// Si la lista esta vacia, nodo *prim = NULL
// Si la lista no esta vacia, nodo *prim != NULL
// El ultimo nodo de la lista apunta a NULL
// Los datos de los nodos estan ordenados y pueden repetirse
/* -------------------------------------------------------------------------- */

typedef struct {
	struct nodo *prim;
} lista_ordenada_t;

struct nodo {
	struct nodo *sig;
	int dato;
};
typedef struct nodo nodo_t;

// Constructor Nodo
nodo_t *nodo_constructor(int dato) {

	nodo_t *nodo = malloc(sizeof(struct nodo));
	if (nodo == NULL)
		return NULL;

	nodo->dato = dato;
	nodo->sig = NULL;

	return nodo;
}

// Destructor lista
void lista_destruir(lista_ordenada_t *l) {
	nodo_t *nodo = l->prim;
	while (nodo != NULL) {
		nodo_t *aux = nodo;
		nodo = nodo->sig;
		free(aux);
	}
	free(l);
}

// Constructor lista
lista_ordenada_t *lista_ordenada_crear() {
	lista_ordenada_t *lista = malloc(sizeof(lista_ordenada_t));
	if (lista == NULL)
		return NULL;

	lista->prim = NULL;

	return lista;
}

// Insertar nodo en lista al final
bool lista_agregar_nodo(lista_ordenada_t *lista, int dato) {

	nodo_t *nodo_aux = lista->prim;
	nodo_t *nodo_nuevo = nodo_constructor(dato);

	if (nodo_nuevo == NULL)
		return false;

	// Si la lista esta vacia
	if (nodo_aux == NULL) {
		lista->prim = nodo_nuevo;
		return true;
	}
	// Busco el ultimo nodo
	while (nodo_aux->sig != NULL)
		nodo_aux = nodo_aux->sig;

	// Agregar el nodo al final
	nodo_aux->sig = nodo_nuevo;
	return true;
}

// Imprimir lista
void lista_imprimir(lista_ordenada_t *lista) {
	nodo_t *nodo = lista->prim;
	while (nodo != NULL) {
		printf("%d ", nodo->dato);
		nodo = nodo->sig;
	}
	printf("\n");
}

/* -------------------------------------------------------------------------- */

bool lista_ordenada_insertar(lista_ordenada_t *l, int dato) {

	nodo_t *nodo_aux = l->prim;
	nodo_t *nodo_nuevo = nodo_constructor(dato);
	if (nodo_nuevo == NULL)
		return false;

	// Si la lista esta vacia
	if (nodo_aux == NULL) {
		l->prim = nodo_nuevo;
		return true;
	}

	// Busco el primer nodo que sea menor o igual al dato
	while (nodo_aux->sig != NULL && nodo_aux->sig->dato <= dato) {
		nodo_aux = nodo_aux->sig;
	}

	nodo_nuevo->sig = nodo_aux->sig;
	nodo_aux->sig = nodo_nuevo;

	return true;
}

int main(void) {

	lista_ordenada_t *lista = lista_ordenada_crear();
	assert(lista != NULL);

	lista_agregar_nodo(lista, 1);
	lista_agregar_nodo(lista, 2);
	lista_agregar_nodo(lista, 3);
	lista_agregar_nodo(lista, 5);
	lista_agregar_nodo(lista, 6);
	lista_agregar_nodo(lista, 8);
	lista_agregar_nodo(lista, 9);

	printf("Lista original:\n");
	lista_imprimir(lista);

	lista_ordenada_insertar(lista, 4);
	lista_ordenada_insertar(lista, 7);
	lista_ordenada_insertar(lista, 2);
	lista_ordenada_insertar(lista, 10);
	lista_ordenada_insertar(lista, 66);

	printf("Lista con los elementos insertados:\n");
	lista_imprimir(lista);

	lista_destruir(lista);

	return 0;
}

#elif N_EJERCICIO == 2

/*
Se pide implementar una función int arreglo_reducir(const int arreglo[], size_t n, int (*f)(int a, int b));
que reciba un arreglo de n enteros y le aplique, de a pares, la función f a sus elementos y al resultado de
la operación. Si el arreglo tuviera sólo un elemento se debe devolver ese elemento, si tuviera más de uno,
el resultado se originará de la función f.
Ejemplo, si el arreglo fuera {1, 2, 4, 6} y f fuera la suma se debería devolver 13;
en cambio si f fuera el producto se debería devolver 48.
*/

int arreglo_reducir(const int arreglo[], size_t n, int (*f)(int a, int b)) {
	if (n <= 1)
		return arreglo[0];
	return f(arreglo_reducir(arreglo, n / 2, f), arreglo_reducir(arreglo + n / 2, n - n / 2, f));
}

int suma(int a, int b) {
	return a + b;
}

int producto(int a, int b) {
	return a * b;
}

int main(void) {

	int a[] = {1, 2, 4, 6, 3};
	int b[] = {1, 2, 4, 6};
	int c[] = {1};

	size_t n_a = sizeof(a) / sizeof(a[0]);
	size_t n_b = sizeof(b) / sizeof(b[0]);
	size_t n_c = sizeof(c) / sizeof(c[0]);

	printf("La suma de los elementos es: %d\n", arreglo_reducir(a, n_a, suma));
	printf("El producto de los elementos es: %d\n", arreglo_reducir(a, n_a, producto));

    printf("La suma de los elementos es: %d\n", arreglo_reducir(b, n_b, suma));
    printf("El producto de los elementos es: %d\n", arreglo_reducir(b, n_b, producto));

    printf("La suma de los elementos es: %d\n", arreglo_reducir(c, n_c, suma));
    printf("El producto de los elementos es: %d\n", arreglo_reducir(c, n_c, producto));

	return 0;
}

#elif N_EJERCICIO == 3

size_t ocurrencias_de_caracter_recursivo(char *a, char caracter) {
	if (*a == '\0')
		return 0;
	if (*a == caracter)
		return 1 + ocurrencias_de_caracter_recursivo(a + 1, caracter);
	return ocurrencias_de_caracter_recursivo(a + 1, caracter);
}

int main(void) {

	char *a = "Mississippi";

    printf("%s\n", a);
	printf("[i] Resultado: %zu. Se espera: 4\n", ocurrencias_de_caracter_recursivo(a, 'i'));
	printf("[s] Resultado: %zu. Se espera: 4\n", ocurrencias_de_caracter_recursivo(a, 's'));
    printf("[a] Resultado: %zu. Se espera: 0\n", ocurrencias_de_caracter_recursivo(a, 'a'));

    puts("");

    char *b = "";
    printf("(Cadena vacia)\n");
    printf("[i] Resultado: %zu. Se espera: 0\n", ocurrencias_de_caracter_recursivo(b, 'i'));

    puts("");

    char *c = "Buenas noches americaaaaaaaa";
    printf("%s\n", c);
    printf("[a] Resultado: %zu. Se espera: 10\n", ocurrencias_de_caracter_recursivo(c, 'a'));
    puts("");

	return 0;
}

#endif