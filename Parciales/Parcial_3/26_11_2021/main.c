/**
 * @file main.c
 * @author Rodriguez Guido Ezequiel (guerodriguez@fi.uba.ar)
 * @note Padron 108723
 * @version 1.0
 * @date 2021-26-11
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

#define N_EJERCICIO 3

#if N_EJERCICIO == 1

// Luego del bochorno de las elecciones del 2015 la AFA quiere establecer un sistema
// de votación digital. En estas elecciones no hay candidatos postulados sino que cada
// uno de los asambleístas presentes vota porquien él considera apropiado

// Se pide modelar el TDA votación que permita llevar adelante la elección.
// Se pide:

// a.Declarar la estructura que encapsula el TDA. Explicar qué representa cada miembro y
// documentar el invariante de representación.

// b.Implementar la primitiva char *votacion_ganador(const votacion_t *v);
// que devuelva el nombre del ganador de la elección.
// (Como la cantidad de asambleístas es impar no puede haber un empate. . . o sí puede, pero
// en el caso de empate devolver cualquiera de los ganadores.)

// c.Implementar la primitiva bool votacion_votar(votacion_t *v, const char *nombre);
// que emita un sufragio a favor de la persona identificada con el nombre dado.

/* -------------------------------------------------------------------------- */
// Invariante de representacion:
/* -------------------------------------------------------------------------- */
// - Si n_candidatos == 0, entonces candidatos == NULL
// - Si n_candidatos > 0, entonces candidatos != NULL
// - No hay candidatos repetidos
// - Todos los punteros apuntan a memoria valida
/* -------------------------------------------------------------------------- */

#define MAX 100

typedef struct {
    char nombre[MAX];    // Nombre del candidato (String estatico de MAX caracteres)
    size_t votos;        // Cantidad de votos que recibio el candidato
} candidato_t;

typedef struct {
    candidato_t *candidatos;    // Puntero a un arreglo dinamico de candidatos
    size_t n_candidatos;        // Cantidad de candidatos
} votacion_t;

/**
 * @brief  Funcion que devuelve una cadena con el nombre del candidato con mas votos
 * @note   Si n_candidatos = 0, se retorna NULL
 * @param  *v: Puntero a una estructura votacion_t
 * @retval Puntero a una cadena con el nombre del candidato con mas votos
 */
char *votacion_ganador(const votacion_t *v) {

    // Si no hay candidatos, retornar NULL
    if (v->n_candidatos == 0)
        return NULL;

    // Busco el candidato con mas votos
    size_t pos_ganador = 0;
    size_t votos_totales = v->candidatos[0].votos;

    for (size_t i = 1; i < v->n_candidatos; i++) {

        if (v->candidatos[i].votos > votos_totales) {

            votos_totales = v->candidatos[i].votos;

            pos_ganador = i;
        }
    }

    return v->candidatos[pos_ganador].nombre;
}

/**
 * @brief  Funcion que emite un voto a favor de un candidato
 * @param  *v: Puntero a una estructura votacion_t
 * @param  *nombre: Puntero a una cadena con el nombre del candidato
 * @retval true si se pudo emitir el voto, false en caso contrario u otro error
 */
bool votacion_votar(votacion_t *v, const char *nombre) {

    // Verifico si el candidato existe previamente
    for (size_t i = 0; i < v->n_candidatos; i++) {
        if (strcmp(v->candidatos[i].nombre, nombre) == 0) {
            v->candidatos[i].votos++;
            return true;
        }
    }

    // En caso de que no exista y alguien lo voto, lo creo y le sumo 1 voto
    candidato_t *candidatos_aux = realloc(v->candidatos, (v->n_candidatos + 1) * sizeof(candidato_t));
    if (candidatos_aux == NULL) {
        return false;
    }
    v->candidatos = candidatos_aux;

    strcpy(v->candidatos[v->n_candidatos].nombre, nombre);
    v->candidatos[v->n_candidatos].votos = 1;
    v->n_candidatos++;

    return true;
}

int main(void) {

    votacion_t votacion = {
        .candidatos = NULL,
        .n_candidatos = 0};

    votacion_t *p_votacion = &votacion;

    assert(votacion_votar(p_votacion, "Juan"));
    assert(votacion_votar(p_votacion, "Juan"));
    assert(votacion_votar(p_votacion, "Juan"));
    assert(votacion_votar(p_votacion, "Juan"));
    assert(votacion_votar(p_votacion, "Juan"));

    assert(votacion_votar(p_votacion, "Pedro"));
    assert(votacion_votar(p_votacion, "Pedro"));
    assert(votacion_votar(p_votacion, "Pedro"));
    assert(votacion_votar(p_votacion, "Pedro"));

    assert(votacion_votar(p_votacion, "Maria"));
    assert(votacion_votar(p_votacion, "Maria"));
    assert(votacion_votar(p_votacion, "Maria"));
    assert(votacion_votar(p_votacion, "Maria"));
    assert(votacion_votar(p_votacion, "Maria"));
    assert(votacion_votar(p_votacion, "Maria"));

    // Muestro los candidatos y sus votos
    for (size_t i = 0; i < p_votacion->n_candidatos; i++)
        printf("%s: %zu\n", p_votacion->candidatos[i].nombre, p_votacion->candidatos[i].votos);

    char *ganador = votacion_ganador(p_votacion);
    if (ganador != NULL)
        printf("El/La ganador/a es %s\n", ganador);
    else
        fprintf(stderr, "Ocurrio un error. ¯\\_(ツ)_/¯\n");

    // "Destructor"
    free(p_votacion->candidatos);

    return 0;
}

#elif N_EJERCICIO == 2

// Se tiene un archivo binario en el cual se escribieron cadenas de caracteres de
// longitud variable como unasecuencia desize_tque dicen el largonde la próxima
// cadena y luego una secuencia dencaracteres, por ejemplo
// +----+-----+-----+----+-----+----+-----+-----+
// | 2  |'9'  |'5'  | 1  |'.'  | 2  |'1'  |'1'  |
// +----+-----+-----+----+-----+----+-----+-----+
// para un archivo que contiene las cadenas{"95", ".", "11"}.
// Se pide escribir una funciónchar *leer_cadena(FILE *f);
// que dado un archivo ya abierto en modo delectura binaria lea una cadena.
// Si el archivo se hubiera terminado debe devolver la cadena vacía.
// Si hubiera alguna falla debe devolver NULL.

char *leer_cadena(FILE *f) {

    // Leo el largo de la cadena
    size_t largo;
    if (fread(&largo, sizeof(size_t), 1, f) != 1)
        return NULL;

    // Creo un buffer para leer la cadena
    char *buffer = malloc(largo + 1);    // +1 para el centinela
    if (buffer == NULL)
        return NULL;

    // Leo la cadena
    if (fread(buffer, sizeof(char), largo, f) != largo) {
        free(buffer);
        return NULL;
    }

    // Termino la cadena con un caracter nulo
    buffer[largo] = '\0';

    return buffer;
}

int main(void) {

    /* -------------------------------------------------------------------------- */
    // Creacion de archivo de prueba
    /* -------------------------------------------------------------------------- */

    FILE *f = fopen("prueba.bin", "wb");
    if (f == NULL) {
        fprintf(stderr, "Error al crear el archivo de prueba.\n");
        return 1;
    }
    fwrite(&(size_t){2}, sizeof(size_t), 1, f);
    fwrite("95", sizeof(char), 2, f);
    fwrite(&(size_t){1}, sizeof(size_t), 1, f);
    fwrite(".", sizeof(char), 1, f);
    fwrite(&(size_t){2}, sizeof(size_t), 1, f);
    fwrite("11", sizeof(char), 2, f);

    fclose(f);
    /* -------------------------------------------------------------------------- */

    FILE *f2 = fopen("prueba.bin", "rb");
    if (f2 == NULL) {
        fprintf(stderr, "Error al abrir el archivo de prueba.\n");
        return 1;
    }

    char *cadena;
    while ((cadena = leer_cadena(f2)) != NULL) {
        printf("%s\n", cadena);
        free(cadena);
    }

    fclose(f2);

    return 0;
}

#elif N_EJERCICIO == 3

// Dado el formato (y la función) del ejercicio 2 escribir un programa que se ejecute:
// $ ./leer_n_cadenas entrada n
// que imprima las primerasncadenas del archivo
// binario entrada como líneas por stdout.
// (Debe utilizarsela función previamente desarrollada.)

char *leer_cadena(FILE *f) {

    // Leo el largo de la cadena
    size_t largo;
    if (fread(&largo, sizeof(size_t), 1, f) != 1)
        return NULL;

    // Creo un buffer para leer la cadena
    char *buffer = malloc(largo + 1);    // +1 para el centinela
    if (buffer == NULL)
        return NULL;

    // Leo la cadena
    if (fread(buffer, sizeof(char), largo, f) != largo) {
        free(buffer);
        return NULL;
    }

    // Termino la cadena con un caracter nulo
    buffer[largo] = '\0';

    return buffer;
}

int main(int argc, char **argv) {

    /* -------------------------------------------------------------------------- */
    // Creacion de archivo de prueba
    /* -------------------------------------------------------------------------- */

    FILE *f = fopen("prueba.bin", "wb");
    if (f == NULL) {
        fprintf(stderr, "Error al crear el archivo de prueba.\n");
        return 1;
    }
    fwrite(&(size_t){2}, sizeof(size_t), 1, f);
    fwrite("95", sizeof(char), 2, f);
    fwrite(&(size_t){1}, sizeof(size_t), 1, f);
    fwrite(".", sizeof(char), 1, f);
    fwrite(&(size_t){2}, sizeof(size_t), 1, f);
    fwrite("11", sizeof(char), 2, f);

    fclose(f);
    /* -------------------------------------------------------------------------- */

    if (argc != 3) {
        fprintf(stderr, "Uso: ./main <archivo> <n_cadenas>\n");
        return 1;
    }

    FILE *f_r = fopen(argv[1], "rb");
    if (f_r == NULL) {
        fprintf(stderr, "Error al abrir el archivo de prueba.\n");
        return 1;
    }

    char *cadena;
    char *err_ptr;
    size_t n = strtoul(argv[2], &err_ptr, 10);
    if (*err_ptr != '\0') {
        fprintf(stderr, "Error en el argumento n_cadenas.\n");
        return 1;
    }
    size_t i = 0;

    for (; i < n && (cadena = leer_cadena(f_r)) != NULL; i++) {
        printf("%s\n", cadena);
        free(cadena);
    }

    fclose(f_r);

    if (i < n)
        fprintf(stderr, "Advertencia: La cantidad de cadenas leidas es menor a la solicitada. Se leyeron %zu.\n", i);

    return 0;
}

#endif