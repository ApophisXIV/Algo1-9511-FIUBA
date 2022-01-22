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

#define EJ 2

#if EJ == 1

/* 1. Teniendo un TDA lista enlazada definida como

typedef struct {
    struct nodo *prim;
} lista_t;

y su nodo como

struct nodo {
    struct nodo *sig;
    void *dato;
};

implementar una primitiva

lista_t *lista_limpiar(const lista_t *l, bool (*criterio)(const void *), void (*eliminar)(void *));
que reciba una lista l y elimine todos los nodos donde criterio devuelva true. Los datos se liberan con la función
eliminar*/

typedef struct
{
    struct nodo *prim;
} lista_t;

typedef struct nodo
{
    struct nodo *sig;
    void *dato;
} nodo_t;


lista_t *lista_crear()
{
    lista_t *l = malloc(sizeof(lista_t *));
    if (l == NULL)
        return NULL;

    l->prim = NULL;

    return l;
}

nodo_t *nodo_crear(void* dato)
{
    nodo_t *nodo = malloc(sizeof(struct nodo));
    if (nodo == NULL)
        return NULL;

    nodo->dato = dato;
    nodo->sig = NULL;

    return nodo;
}


bool lista_insertar_al_final(lista_t *l, void *dato) {

	nodo_t *nuevo_nodo = nodo_crear(dato);
	if (nuevo_nodo == NULL) {
		return false;
	}

    nodo_t *act = l->prim;
    if (l->prim == NULL)
    {
        l->prim = nuevo_nodo;
        return true;
    }


	while ((act->sig) != NULL)
	    act = act->sig;

	act->sig = nuevo_nodo;
	return true;
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


bool criterio(const void *dato)
{
    return strcmp((char *) dato, "hola") == 0;
}

void eliminar(void *dato)
{
    dato = NULL;
}

/*  recibe una lista l y elimine todos los nodos donde criterio devuelva true. Los datos se liberan con la función
 eliminar*/
lista_t *lista_limpiar(const lista_t *l, bool (*criterio)(const void *)){

    nodo_t *nodo_actual_aux = l->prim;

    while (nodo_actual_aux != NULL)
    {
        if (criterio(nodo_actual_aux->dato))
        {
            printf("%s\n", (char*)nodo_actual_aux->dato);
            eliminar(nodo_actual_aux->dato);

        }
        else
        {
            nodo_actual_aux = nodo_actual_aux->sig;
        }
    }

    return l;
}


void lista_imprimir(lista_t *lista) {
	nodo_t *nodo = lista->prim;
	while (nodo != NULL) {
		printf("%s ", (char *)nodo->dato);
		nodo = nodo->sig;
	}
	printf("\n");
}

int main(void)
{
    lista_t *l = lista_crear();
    if(l  == NULL) return 1;

    lista_insertar_al_final(l, "hola");
    lista_insertar_al_final(l, "mundo");
    lista_insertar_al_final(l, "hola");
    lista_insertar_al_final(l, "chau");
    lista_insertar_al_final(l, "109111");
    lista_insertar_al_final(l, "juan");
    lista_insertar_al_final(l, "pedro");
    lista_insertar_al_final(l, "pedro");
    lista_insertar_al_final(l, "sofia");
    lista_insertar_al_final(l, "108245");

    lista_imprimir(l);

    lista_limpiar(l, criterio);

     lista_destruir(l);

    return 0;
}

#elif EJ == 2

/* 2. Se tiene un listado ordenado con los padrones de todos los alumnos cursando Algoritmos. También se tiene un
listado ordenado con los padrones de todos los alumnos cursando Física. Implementar una función int
*alumnos_complicados(const int *aalgoritmos[], size_t nalgoritmos, const int *nfisica[], size_t nfisica, size_t
*ncomplicados); que devuelva el listado de alumnos a los que la gente del departamento de Física va a complicar
gratuitamente si superpone sus parciales con los de Algoritmos, es decir, todos los que estén cursando ambas materias.
Se debe devolver la cantidad en ncomplicados. Asumir, al igual que lo hacen ellos, que siempre pueden complicarle la
vida a alguien.*/

//#quemar_depto_fisica
int *alumnos_complicados(const int *aalgoritmos[], size_t nalgoritmos, const int *nfisic[], size_t nfisica, size_t *ncomplicados)
{

    printf("Algoritmos: ");

    //Imprimo los alumnos de Algoritmos
    for (int i = 0; i < nalgoritmos; i++)
    {
        printf("%d ", aalgoritmos[i]);
    }

    printf("Fisica: ");
    //Imprimo los alumnos de Física
    for (int i = 0; i < nfisica; i++)
    {
        printf("%d ", nfisic[i]);
    }
    printf("\n");

    //Creo una lista de alumnos complicados
    // int *alumnos_complicados = malloc((nalgoritmos < nfisica ? nalgoritmos : nfisica) *sizeof(int *)); // cual es mas chico, el mas grande lo toma el malloc

    // if (alumnos_complicados == NULL)
    //     return NULL;

    // //Creo un contador de alumnos complicados
    // int contador = 0;

    // //Recorro los alumnos de Algoritmos
    // for (int i = 0; i < nalgoritmos; i++)
    // {
    //     //Recorro los alumnos de Física
    //     for (int j = 0; j < nfisica; j++)
    //     {
    //         //Si el alumno de Algoritmos está cursando Física
    //         if (aalgoritmos[i] == nfisic[j])
    //         {
    //             //Lo agrego a la lista de alumnos complicados
    //             alumnos_complicados[contador] = aalgoritmos[i];
    //             contador++;
    //         }
    //     }
    // }

    // //Devuelvo la cantidad de alumnos complicados
    // *ncomplicados = contador;

    return NULL;
}
int main (void){

    int aalgoritmos[] = {1,2,3,4,5,6,7,8,9,10};
    int nfisic[] = {2,4,6,8,10};
    size_t nalgoritmos = sizeof(aalgoritmos) / sizeof(int);
    size_t nfisica = sizeof(nfisic) / sizeof(int);
    size_t ncomplicados;

    int *alumnos_c = alumnos_complicados(aalgoritmos, 10, nfisic, 5, &ncomplicados);

    printf("Alumnos complicados: ");
    for (int i = 0; i < ncomplicados; i++)
    {
        printf("%d ", alumnos_c[i]);
    }
    printf("\n");

    return 0;
}

#elif EJ == 3

/*3. Escribir una función recursiva
int sumar_pares(int v[], size_t n);
que devuelva la suma de los elementos pares del vector v. Por ejemplo para {2, 3, 5, 6, 8} debe devolverse 16.
Si bien cada uno de los ejercicios es independiente de los demás se deberán codificar todas las funciones en un único
archivo de código fuente que será el que se entregue. */

// Suma los elementos que sean pares de un vector de forma recursiva
int sumar_pares(int v[], size_t n)
{
    if (n == 0)
        return 0;
    else if (!(v[n - 1] % 2))
        return v[n - 1] + sumar_pares(v, n - 1);
    else
        return sumar_pares(v, n - 1);
}

int main(void)
{
    int v[] = {2, 3, 5, 6, 8};
    printf("%d\n", sumar_pares(v, 5));

    return 0;
}

#endif
