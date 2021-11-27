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

#define MAX_CADENA 10

typedef struct {
    char nombre[MAX_CADENA];
    unsigned int padron;
    float promedio;
} alumno_t;

bool alumno_son_iguales(const alumno_t *a, const alumno_t *b) {
    return strcmp(a->nombre, b->nombre) == 0 && a->padron == b->padron && a->promedio == b->promedio;
}

int main(void) {

    alumno_t a1 = {.nombre = "Ezequiel", .padron = 108723, .promedio = 8.5};
    alumno_t a2 = {.nombre = "Pepe", .padron = 101723, .promedio = 1.5};

    printf("%s\n", alumno_son_iguales(&a1, &a2) ? "Son iguales" : "No son iguales");
    printf("%s\n", alumno_son_iguales(&a1, &a1) ? "Son iguales" : "No son iguales");

    return 0;
}

#elif N_EJERCICIO == 2

typedef struct {
    float *v;
    size_t n;
} vector_t;

vector_t *vector_crear(const float vals[], size_t n) {

    vector_t *v = malloc(sizeof(vector_t));
    if (v == NULL)
        return NULL;

    v->v = malloc(n * sizeof(float));
    if (v->v == NULL) {
        free(v);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        v->v[i] = vals[i];
    }

    v->n = n;

    return v;
}

void vector_destruir(vector_t *v) {
    free(v->v);
    free(v);
}

int main(void) {

    float vals[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector_t *v = vector_crear(vals, 5);

    printf("%f\n", v->v[0]);
    printf("%f\n", v->v[1]);
    printf("%f\n", v->v[2]);
    printf("%f\n", v->v[3]);
    printf("%f\n", v->v[4]);

    vector_destruir(v);

    return 0;
}

#elif N_EJERCICIO == 3

bool leer_enteros(int **pv, size_t *n) {

    int *v = NULL;
    size_t n_v = 0;

    char buffer[100];
    while (fgets(buffer, 100, stdin) != NULL) {

        int *v_aux = realloc(v, sizeof(int *) * (n_v + 1));
        if (v_aux == NULL) {
            return false;
        }

        v = v_aux;
        v[n_v++] = atoi(buffer);
    }

    *pv = v;
    *n = n_v;

    return true;
}

int main(void) {

    int *v = NULL;
    size_t n = 0;

    printf("Ingrese numeros enteros\n");
    
    if (!leer_enteros(&v, &n)) {
        fprintf(stderr, "Error al leer la entrada");
        return 1;
    }

    printf("Enteros leidos\n");

    for (size_t i = 0; i < n; i++)
        printf("%d\n", v[i]);

    free(v);

    return 0;
}

#endif
