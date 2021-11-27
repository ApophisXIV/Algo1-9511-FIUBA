/**
 * @file main.c
 * @author Rodriguez Guido Ezequiel (guerodriguez@fi.uba.ar)
 * @Note Padron 108723
 * @version 1.0
 * @date 2021-11-5
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_EJERCICIO 3

#if N_EJERCICIO == 1

/*Teniendo una listade enterosen la cual la lista se representatypedef struct {struct nodo *prim;} lista_t;yel nodo se representa comostruct nodo {struct nodo *sig; int dato;};implementar la primitivavoid lista_enteros_borrar(lista_t *l, int e);que borre todas las ocurrencias del datoeen la lista.*/

typedef struct nodo {
    struct nodo *sig;
    int dato;
} nodo_t;

typedef struct {
    nodo_t *prim;
} lista_t;

void lista_enteros_borrar(lista_t *l, int e) {

    nodo_t *aux = l->prim;

    if (aux == NULL) {
        return;
    }

    if (aux->dato == e) {
        l->prim = aux->sig;
        free(aux);
        lista_enteros_borrar(l, e);
    } else {
        while (aux->sig != NULL) {
            if (aux->sig->dato == e) {
                nodo_t *aux2 = aux->sig;
                aux->sig = aux2->sig;
                free(aux2);
                lista_enteros_borrar(l, e);
            }
            aux = aux->sig;
        }
    }
}

int main(void) {

    nodo_t *nodo1 = malloc(sizeof(nodo_t));
    nodo_t *nodo2 = malloc(sizeof(nodo_t));
    nodo_t *nodo3 = malloc(sizeof(nodo_t));

    nodo1->dato = 1;
    nodo2->dato = 2;
    nodo3->dato = 3;

    printf("%d\n", nodo1->dato);
    printf("%d\n", nodo2->dato);
    printf("%d\n", nodo3->dato);

    nodo1->sig = nodo2;
    nodo2->sig = nodo3;
    nodo3->sig = NULL;

    lista_t *l = malloc(sizeof(lista_t));

    l->prim = nodo1;

    lista_enteros_borrar(l, 2);

    printf("%d\n", nodo1->dato);
    printf("%d\n", nodo2->dato);
    printf("%d\n", nodo3->dato);

    // free(nodo1);
    // free(nodo2);
    // free(nodo3);
    // free(l);

    return 0;
}

#elif N_EJERCICIO == 2

int main(void) {
}

#elif N_EJERCICIO == 3

/*
Se representa a un color RGB de 24 bits como un entero sin signo0xAABBCCdonde el byte0xAArepresenta el rojo,0xBBel verde y0xCCel azul. Se pide:

a.Implementar la funciónunsigned char get_rojo(unsigned int color);que devueva el valor de la componenteroja.

b.Implementar la funciónvoid set_verde(unsigned int *color, unsigned char verde);que cargue la com-ponente deverdeen elcolorrecibido
*/

#define RED 0xFF0000

unsigned char get_rojo(unsigned int color){
    return (color & RED) >> 16;
}

#define VERDE 0x00FF00
void set_verde(unsigned int *color, unsigned char verde){
    *color = (*color & ~VERDE) | (verde << 8);
}

int main(void) {
    unsigned int color = 0xb40145;
    printf("%X\n", get_rojo(color));
    set_verde(&color, 0xAF);
    printf("%X\n", color);
    return 0;
}

#endif
