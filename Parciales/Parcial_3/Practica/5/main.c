/**
 * @file main.c
 * @author Rodriguez Guido Ezequiel (guerodriguez@fi.uba.ar)
 * @Note Padron 108723
 * @version 1.0
 * @date 2021-26-11
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_EJERCICIO 1

#if N_EJERCICIO == 1

/*
 Se quiere modelar el TDA votación, el cual contiene una determinada cantidad de cadenas que representan las opcionesy los votos que tuvo cada opción.
 a) Declarar la estructura que encapsula el TDA. Explicar qué representa cada miembro y documentar el invariante derepresentación.
 b) Implementar la primitivaunsigned int votacion_votos_totales(const votacion_t *v);que devuelva lacantidad de votos totales de todas las opciones.
 c) Implementar la primitivabool votacion_agregar_opcion(votacion_t *v, const char *opcion);que agre-gue la opción a la lista de opciones.
 */

// Invariante de representacion:
// - Si n_opciones = 0, opciones = NULL
// - Si n_opciones > 0, opciones != NULL
// - No se puede agregar una opcion si ya existe una con el mismo nombre
// - La dimension del arreglo de opcion_t apuntado por opciones es igual al numero expresado por n_opciones
// - Todos los punteros apuntan a direcciones de memoria valida

#define MAX 100

typedef struct {
    char nombre[MAX];    // Arreglo estatico de caracteres que representa el nombre de la opcion
    size_t votos;        // Variable que representa la cantidad de votos que tuvo la opcion
} opcion_t;

typedef struct {
    size_t n_opciones;     // Variable que registra el numero de opciones. Si n_opciones = 0, opciones = NULL
    opcion_t *opciones;    // Puntero a arreglo de opcion_t donde se almacenan las opciones
} votacion_t;

/**
 * @brief   Funcion que devuelve la cantidad de votos totales de todas las opciones
 * @note    Si n_opciones = 0, se retorna 0
 * @param   *v: Puntero a votacion_t
 * @retval  La cantidad de votos totales de todas las opciones
 */
unsigned int votacion_votos_totales(const votacion_t *v) {
    size_t total = 0;
    for (size_t i = 0; i < v->n_opciones; i++)
        total += v->opciones[i].votos;
    return total;
}

/**
 * @brief   Funcion que agrega una opcion a la lista de opciones
 * @note    Si n_opciones = 0, se crea un arreglo de opciones con una capacidad de 1
 * @param  	*v:  Puntero a votacion_t
 * @param  	*opcion: Puntero a char que representa el nombre de la opcion
 * @retval	true: Si la opcion fue agregada con exito
 * @retval	false: Si la opcion no fue agregada
 */
bool votacion_agregar_opcion(votacion_t *v, const char *opcion) {

    //Verifico que la opcion no exista
    for (size_t i = 0; i < v->n_opciones; i++)
        if (strcmp(v->opciones[i].nombre, opcion) == 0)
            return false;

    opcion_t *aux = realloc(v->opciones, (v->n_opciones + 1) * sizeof(opcion_t));
    if (aux == NULL)
        return false;
    v->opciones = aux;
    v->n_opciones++;

    strcpy(v->opciones[v->n_opciones - 1].nombre, opcion);
    v->opciones[v->n_opciones - 1].votos = 0;

    return true;
}

int main(void) {

    votacion_t votacion = {0, NULL};
    votacion_t *p_votacion = &votacion;

    votacion_agregar_opcion(p_votacion, "A");
    votacion_agregar_opcion(p_votacion, "B");
    votacion_agregar_opcion(p_votacion, "C");

    votacion.opciones[0].votos = 1;
    votacion.opciones[1].votos = 2;
    votacion.opciones[2].votos = 3;

    printf("Votos totales %u\n", votacion_votos_totales(p_votacion));

    free(p_votacion->opciones);

    return 0;
}

#elif N_EJERCICIO == 2

bool escribir_doubles(const char *r, const double a[], size_t n) {

    FILE *archivo = fopen(r, "wb");
    if (archivo == NULL)
        return false;

    if (fwrite(&n, sizeof(size_t), 1, archivo) != 1)
        return false;

    if (fwrite(a, sizeof(double), n, archivo) != n)
        return false;

    fclose(archivo);

    return true;
}

/**
 * @brief  Funcion que lee un arreglo de doubles desde un archivo binario
 * @note   Si el archivo no existe, se retorna false
 * @param  *r: Puntero a char que representa el nombre del archivo
 * @param  *n: Puntero a size_t que representa la cantidad de doubles que se leeran
 * @retval true: Si el archivo fue leido con exito
 * @retval false: Si el archivo no fue leido
 */
double *leer_doubles(const char *r, size_t *n) {

    *n = 0;

    FILE *archivo = fopen(r, "rb");
    if (archivo == NULL)
        return NULL;

    if (fread(n, sizeof(size_t), 1, archivo) != 1)
        return NULL;

    double *a = malloc(*n * sizeof(double));
    if (a == NULL)
        return NULL;

    if (fread(a, sizeof(double), *n, archivo) != *n)
        return NULL;

    fclose(archivo);

    return a;
}

int main(int argc, char *argv[]) {

    // Creacion de archivo de prueba
    double t[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    if (!escribir_doubles("prueba.bin", t, 5))
        return 1;

    if (argc != 5) {
        fprintf(stderr, "Error en la cantidad de argumentos\n");
        return 1;
    }

    char *errPtr;

    double a = strtod(argv[3],&errPtr);
    if(*errPtr != '\0') {
        fprintf(stderr, "Error en el argumento %s\n", argv[3]);
        return 1;
    }

    double b = strtod(argv[4],&errPtr);
    if(*errPtr != '\0') {
        fprintf(stderr, "Error en el argumento %s\n", argv[4]);
        return 1;
    }

    size_t n;
    double *x = leer_doubles(argv[1], &n);
    if (x == NULL) {
        fprintf(stderr, "Error al leer el archivo %s\n", argv[1]);
        return 1;
    }

    for (size_t i = 0; i < n; i++){
        printf("%f\n", x[i]);
        x[i] = a * x[i] + b;
    }

    if (!escribir_doubles(argv[2], x, n)) {
        fprintf(stderr, "Error al escribir el archivo %s\n", argv[2]);
        return 1;
    }

    //Leer lo que escribi
    double *y = leer_doubles(argv[2], &n);
    if (y == NULL) {
        fprintf(stderr, "Error al leer el archivo %s\n", argv[2]);
        return 1;
    }

    printf("\n");
    for (size_t i = 0; i < n; i++)
        printf("%f\n", y[i]);

    free(x);
    free(y);

    return 0;
}

#elif N_EJERCICIO == 3

int main(void) {

    return 0;
}

#endif