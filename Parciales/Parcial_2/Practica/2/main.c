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

#define N_EJERCICIO 2

#if N_EJERCICIO == 1

#define MAX_CADENA 20

struct persona {
    char nombre[MAX_CADENA];
    unsigned int edad;
    unsigned short nacimiento;
    struct persona *padre;
    struct persona *madre;
};

typedef struct persona persona_t;

bool tiene_padres_mayores(const persona_t *p, short edad) {
    if (p->padre != NULL && p->madre != NULL) {
        return (p->padre->edad - p->edad) > edad || (p->madre->edad - p->edad) > edad;
    }
    return false;
}

int main(void) {

    persona_t p = {"Pepe", 60, 1961, NULL, NULL};
    persona_t m = {"Maria", 40, 1981, NULL, NULL};
    persona_t j = {"Jose", 15, 2006, &p, &m};

    printf("Tiene padres mayores? %s\n", tiene_padres_mayores(&j, 20) ? "Si" : "No");

    return 0;
}

#elif N_EJERCICIO == 2

void destruir_arreglo_cadenas(char *ss[]) {

    for (size_t i = 0; ss[i] != NULL; i++) {
        free(ss[i]);
    }
    free(ss);
}

char **clonar_arreglo_cadenas(char *ss[]) {

    char **s_heap = malloc(sizeof(char *));

    for (size_t i = 0; ss[i] != NULL; i++) {

        char **s_heap_aux = realloc(s_heap, sizeof(char *) * (i + 1));

        if (s_heap_aux == NULL) {
            destruir_arreglo_cadenas(s_heap);
            return NULL;
        }

        s_heap = s_heap_aux;

        s_heap[i] = malloc(sizeof(char) * (strlen(ss[i]) + 1));

        if (s_heap[i] == NULL) {
            destruir_arreglo_cadenas(s_heap);
            return NULL;
        }

        memcpy(s_heap[i], ss[i], sizeof(char) * (strlen(ss[i]) + 1));
        // strcpy(s_heap[i], ss[i]);
        s_heap[i][strlen(ss[i])] = '\0';
    }

    return s_heap;
}

int main(void) {

    char **s2 = clonar_arreglo_cadenas((char *[]){"hola", "mundo", "como", "estas", NULL});

    for (size_t i = 0; s2[i] != NULL; i++) {
        printf("%s ", s2[i]);
    }

    destruir_arreglo_cadenas(s2);

    return 0;
}

#elif N_EJERCICIO == 3

bool leer_flotantes(float **pv, size_t *n) {

    float *linea = NULL;
    size_t n_linea = 0;

    char buffer[100];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        float *linea_aux = realloc(linea, sizeof(float) * (n_linea + 1));

        if (linea_aux == NULL) {
            free(linea);
            return false;
        }
        linea = linea_aux;

        linea[n_linea++] = atof(buffer);
    }

    *pv = linea;
    *n = n_linea;
    return true;
}

int main(void) {

    printf("Ingrese numeros flotantes: \n");

    float *v = NULL;
    size_t n = 0;

    if (!leer_flotantes(&v, &n)) {
        printf("Error al leer los numeros flotantes\n");
        return 1;
    }

    printf("Numeros leidos: \n");

    for (size_t i = 0; i < n; i++) {
        printf("%f\n", v[i]);
    }

    free(v);

    return 0;
}

#endif
