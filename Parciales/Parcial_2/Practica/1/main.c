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

// char *join(char *strs[], size_t n, char delim) {

//     size_t len = 1;
//     for (size_t i = 0; i < n; i++) {
//         len += strlen(strs[i]);
//     }
//     len += n - 1;

//     char *s = malloc(len * sizeof(char));

//     if (s == NULL) {
//         return NULL;
//     }

//     for (size_t i = 0; i < n; i++) {
//         strcat(s, strs[i]);
//         if (i < n - 1) {
//             strcat(s, &delim);
//         }
//     }

//     return s;
// }

char *join(char *strs[], size_t n, char delim) {

    // Calculo la memoria que necesito:
    size_t longitud = 0;
    for (size_t i = 0; i < n; i++)
        longitud += strlen(strs[i]);    // Sumo los largos de las cadenas.
    longitud += n;                      // Sumo los largos de los delimitadores + el '\0'.

    // Pido la memoria:
    char *s = malloc(n * sizeof(char));

    // Armo la cadena:
    strcpy(s, strs[0]);
    // Acá tengo que tener algo para poder meter delim al final, esto sirve:
    size_t pos = strlen(s);
    for (size_t i = 1; i < n; i++) {
        s[pos++] = delim;            // Si voy a usar strcat() después necesito poner el '\0'
        strcpy(s + pos, strs[i]);    // Acá puedo hacer strcat(s, strs[i]), ¿lo malo?, convierto en cuadrático un problema lineal.
        pos += strlen(strs[i]);
    }

    return s;
}

int main(void) {

    char *p = join((char *[]){"hola", "que", "tal"}, 3, ' ');
    printf("%s\n", p);

    free(p);

    return 0;
}

#elif N_EJERCICIO == 2

#define MAX_STR 20

// char **leer_lineas(size_t *n) {
//     *n = 0;

//     char aux[MAX_STR];
//     size_t i = 0;
//     char **ss = NULL;

//     while (fgets(aux, MAX_STR, stdin) != NULL) {
//         char auxaux = realloc(ss, (i + 1) * sizeof(char *));
//         if (auxaux == NULL) {
//             liberar_lineas(ss, i);
//             return NULL;
//         }
//         ss = auxaux;

//         ss[i] = malloc((strlen(aux) + 1) * sizeof(char));
//         if (ss[i] == NULL) {
//             liberar_lineas(ss, i);
//             return NULL;
//         }

//         strcpy(ss[i], aux);
//         i++;
//     }

//     *n = i;
//     return ss;
// }

void liberar_lineas(char **lineas, size_t n) {
    for (size_t i = 0; i < n; i++)
        free(lineas[i]);
    free(lineas);
}

char **leer_lineas(size_t *n) {

    char **str_vec = malloc(sizeof(char *));
    if (str_vec == NULL)
        return NULL;

    char *linea = malloc(sizeof(char));
    if (linea == NULL)
        return NULL;

    char c;
    size_t i = 0;
    size_t n_lineas = 0;

    while ((c = getchar()) != EOF) {

        if (c != '\n') {

            char *linea_aux = realloc(linea, ++i + 1);
            if (linea_aux == NULL) {
                liberar_lineas(str_vec, n_lineas);
                return NULL;
            }
            linea = linea_aux;
            linea[i - 1] = c;
        }

        else {

            linea[i] = '\0';
            i = 0;

            char **str_vec_aux = realloc(str_vec, ++n_lineas * sizeof(char *));

            if (str_vec_aux == NULL) {
                liberar_lineas(str_vec, n_lineas);
                return NULL;
            }

            str_vec = str_vec_aux;
            str_vec[n_lineas - 1] = linea;

            linea = malloc(sizeof(char));
            if (linea == NULL) {
                liberar_lineas(str_vec, n_lineas);
                return NULL;
            }
        }
    }

    free(linea);

    *n = n_lineas;
    return str_vec;
}

int main(void) {

    size_t n_lineas = 0;
    printf("Escrbi strings :\n");

    char **str = leer_lineas(&n_lineas);
    for (size_t j = 0; j < n_lineas; j++) {
        printf("%zu-> ", j);
        printf("%s\n", str[j]);
    }
    liberar_lineas(str, n_lineas);

    return 0;
}

#elif N_EJERCICIO == 3

#define MAX_CADENA 20
#define MAX_NUMEROS 3

typedef struct {
    char referencia[MAX_CADENA];
    unsigned long numero;
} numero_t;

typedef struct {
    char nombre[MAX_CADENA];
    numero_t numeros[MAX_NUMEROS];
} contacto_t;

bool numero_en_contacto(const contacto_t *c, unsigned long numero) {
    for (size_t i = 0; i < MAX_NUMEROS; i++)
        if (c->numeros[i].numero == numero)
            return true;
    return false;
}

int main(void) {

    contacto_t c = {
        .nombre = "Juan",
        .numeros = {
            {.referencia = "123", .numero = 123},
            {.referencia = "456", .numero = 456},
            {.referencia = "789", .numero = 789}
        }
    };

    printf("%s tiene el numero %d? %s\n", c.nombre, 123, numero_en_contacto(&c, 123) ? "Si" : "No");
    printf("%s tiene el numero %d? %s\n", c.nombre, 456, numero_en_contacto(&c, 456) ? "Si" : "No");
    printf("%s tiene el numero %d? %s\n", c.nombre, 789, numero_en_contacto(&c, 789) ? "Si" : "No");
    printf("%s tiene el numero %d? %s\n", c.nombre, 111, numero_en_contacto(&c, 111) ? "Si" : "No");

    return 0;
}

#endif
