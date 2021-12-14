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
typedef struct {
	struct nodo *prim;
} lista_t;

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

void lista_destruir(lista_t *l) {
	nodo_t *nodo = l->prim;
	while (nodo != NULL) {
		nodo_t *aux = nodo;
		nodo = nodo->sig;
		free(aux);
	}
	free(l);
}

/* - - - - - - - - */
lista_t *lista_crear() {
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL)
		return NULL;

	lista->prim = NULL;

	return lista;
}

bool lista_agregar_nodo(lista_t *lista, int dato) {

	nodo_t *nodo_aux = lista->prim;
	nodo_t *nodo_nuevo = nodo_constructor(dato);

	if (nodo_nuevo == NULL) {
		return false;
	}

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

void lista_imprimir(lista_t *lista) {
	nodo_t *nodo = lista->prim;
	while (nodo != NULL) {
		printf("%d ", nodo->dato);
		nodo = nodo->sig;
	}
	printf("\n");
}

/* -------------------------------------------------------------------------- */

lista_t *lista_clonar(const lista_t *l) {

	lista_t *lista = lista_crear();
	if (lista == NULL)
		return NULL;

	nodo_t *nodo_aux = l->prim;
	while (nodo_aux != NULL) {
		if (!lista_agregar_nodo(lista, nodo_aux->dato)) {
			lista_destruir(lista);
			return NULL;
		}
		nodo_aux = nodo_aux->sig;
	}

	return lista;
}

int main(void) {

	lista_t *lista = lista_crear();
	assert(lista != NULL);

	lista_agregar_nodo(lista, 1);
	lista_agregar_nodo(lista, 2);
	lista_agregar_nodo(lista, 3);
	lista_agregar_nodo(lista, 4);
	lista_agregar_nodo(lista, 5);

	lista_t *l_clon = lista_clonar(lista);

	lista_imprimir(lista);
	lista_imprimir(l_clon);

	lista_destruir(lista);
	lista_destruir(l_clon);

	return 0;
}

#elif N_EJERCICIO == 2

/* Se sabe que la combinación de enfermedades aumenta los riesgos
de mortalidad ante el COVID-19. Se tiene un listado ordenado
alfabéticamente de afectados por enfermedades cardíacas y otro listado,
también ordenado alfabéticamente, de afectados por hipertensión. Implementar
una función char **pacientes_prioritarios(char *cardiacos[], size_t n_cardiacos,char *hipertensos[], size_t n_hipertensos, size_t *n_prioritarios);
que reciba dos listados, el de los n_cardiacos ciudadanos cardiacos y el de
los n_hipertensos ciudadanos hipertensos y devuelva el listado de los
ciudadanos con ambas afecciones por el nombre y la cantidad en n_prioritarios.
Se debe devolver un arreglo de cadenas con los nombres. Ahora bien,
no hace falta pedir memoria para cada una de las cadenas, bien puede apuntarse
a los nombres ya recibidos en cardiacos o en hipertensos. */

char **pacientes_prioritarios(char *cardiacos[], size_t n_cardiacos, char *hipertensos[], size_t n_hipertensos, size_t *n_prioritarios) {

	*n_prioritarios = 0;

	char **prioritarios = malloc(sizeof(char *) * ((n_cardiacos < n_hipertensos) ? n_cardiacos : n_hipertensos));
	if (prioritarios == NULL) {
		return NULL;
	}

	size_t n_c = 0;
	while (n_c < n_cardiacos) {

		size_t n_h = 0;
		while (n_h < n_hipertensos) {

			if (strcmp(cardiacos[n_c], hipertensos[n_h]) == 0) {
				prioritarios[*n_prioritarios] = cardiacos[n_c];
				(*n_prioritarios)++;
				break;
			}
			n_h++;
		}

		n_c++;
	}

	return prioritarios;
}

int main(void) {

	char *cardiacos[] = {"Ana", "Juan", "Maria", "Martin", "Pedro"};
	char *hipertensos[] = {"Ana", "Juan", "Martin", "Nilda", "Tomas"};

	size_t n_prioritarios;
	char **prioritarios = pacientes_prioritarios(cardiacos, 5, hipertensos, 5, &n_prioritarios);

	for (size_t i = 0; i < n_prioritarios; i++) {
		printf("Tienen ambas enfermedades: %s\n", prioritarios[i]);
	}

	free(prioritarios);

	return 0;
}

#elif N_EJERCICIO == 3

/*Escribir una función recursiva que reciba dos cadenas de caracteres y
devuelva la cantidad deveces que la segunda cadena aparece en la primera.
Por ejemplo, la cadena"ssi"se encuentra dos veces en la cadena"Mississippi"
(Ayuda: La función strncmp(const char *s1, const char *s2, size_t n);
compara los primeros n caracteres de s1 y s2.)
*/
size_t mi_strstr_especial_recursivo(char *a, char *b) {

	if (strlen(a) < strlen(b)) {
		return 0;
	}

	if (strncmp(a, b, strlen(b)) == 0) {
		return 1 + mi_strstr_especial_recursivo(a + strlen(b), b);
	}

	return mi_strstr_especial_recursivo(a + 1, b);
}

int main(void) {

	char *a = "Mississippi";
	char *b = "ssi";

	printf("Resultado: %zu. Se espera: 2\n", mi_strstr_especial_recursivo(a, b));

	return 0;
}

#endif