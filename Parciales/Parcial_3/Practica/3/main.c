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

#define N_EJERCICIO 3

#if N_EJERCICIO == 1

// Invariante
//  - Si n_c = 0, coeficiente = NULL
//  - Si n_c > 0, coeficiente != NULL
//  - La dimension del arreglo de doubles apuntado por coeficientes es igual al numero expresado por n_c
//  - El grado del polinomio es igual al numero expresado por n_c - 1 si n_c > 0
//  - Todos los punteros apuntan a direcciones de memoria valida

typedef struct {
    size_t n_c;             // variable que registra el numero de coeficientes
    double *coeficiente;    // Puntero a arreglo de doubles donde se almacenan los coeficientes asociados
} polinomio_t;

/**
 * @brief  Funcion que calcula el valor de un polinomio en un punto dado
 * @pre    El polinomio debe estar inicializado
 * @post   El polinomio no se modifica
 * @note   Si n_c = 0, se retorna 0
 * @param  *p: Puntero a polinomio_t
 * @param  x: Punto en el que se evalua el polinomio
 * @retval Valor del polinomio en el punto x
 */
double polinomio_evaluar(const polinomio_t *p, double x) {

    double resultado = 0;

    for (size_t i = 0; i < p->n_c; i++)
        resultado += p->coeficiente[i] * pow(x, i);

    return resultado;
}

/**
 * @brief   Funcion que calcula el valor de un polinomio en un punto dado
 * @pre     El polinomio debe estar inicializado
 * @post    El polinomio no se modifica
 * @param   *p: Puntero a polinomio_t
 * @retval  Valor del polinomio en el punto x.
 * @retval  Si n_c = 0, se retorna NULL
 * @retval  Si ocurrio un error, se retorna NULL
 */
polinomio_t *polinomio_derivar(const polinomio_t *p) {

    if (p->n_c == 0)
        return NULL;

    polinomio_t *p_dx = malloc(sizeof(polinomio_t));
    if (p_dx == NULL)
        return NULL;

    p_dx->n_c = p->n_c - 1;

    double *c_aux = malloc(p_dx->n_c * sizeof(double));
    if (c_aux == NULL)
        return NULL;
    p_dx->coeficiente = c_aux;

    for (size_t i = 0; i < p_dx->n_c; i++)
        p_dx->coeficiente[i] = p->coeficiente[i + 1] * (i + 1);

    return p_dx;
}

int main(void) {

    polinomio_t p = {
        .n_c = 3,
        .coeficiente = (double[]){1, 2, 3}};

    // Polinomio de grado 2
    //  1 + 2x + 3x^2
    // Resultado esperado: 17
    assert(polinomio_evaluar(&p, 2.0) == 17);
    printf("%f\n", polinomio_evaluar(&p, 2.0));

    polinomio_t *p_dx_1 = polinomio_derivar(&p);
    // Polinomio de grado 1 evaluado en 2.0
    //  2 + 6x
    // Resultado esperado: 14
    assert(polinomio_evaluar(p_dx_1, 2.0) == 14);
    printf("%f\n", polinomio_evaluar(p_dx_1, 2.0));

    //"Destructor"
    free(p_dx_1->coeficiente);
    free(p_dx_1);

    return 0;
}

#elif N_EJERCICIO == 2

#define MAX 100

typedef struct {
    char nombre[MAX];
    unsigned int dni;
    float altura;
} persona_t;

bool leer_persona(FILE *f, persona_t *p) {
    return fread(p, sizeof(persona_t), 1, f);
}

void escribir_persona(FILE *f, const persona_t *p) {
    fprintf(f, "%s,%u,%.2f", p->nombre, p->dni, p->altura);
}

bool leer_personas(const char *r, persona_t v[], size_t max, size_t *n) {

    *n = 0;

    FILE *f = fopen(r, "rb");
    if (f == NULL)
        return false;

    while ((*n) < max)
        if (!leer_persona(f, &v[(*n)++])){
            fclose(f);
            return false;
        }

    fclose(f);

    return true;
}

int main(void) {

    // Creacion de personas en archivo binario
    persona_t personas[10] = {
        {"Juan", 12345678, 1.75},
        {"Pedro", 23456789, 1.75},
        {"Maria", 34567890, 1.75},
        {"Julia", 45678901, 1.75},
        {"Jose", 56789012, 1.75},
        {"Ana", 67890123, 1.75},
        {"Luis", 78901234, 1.75},
        {"Sara", 89012345, 1.75},
        {"Juana", 90123456, 1.75},
        {"Pablo", 12345678, 1.75}};

    FILE *f_personas_bin = fopen("personas.bin", "wb");
    if (f_personas_bin == NULL) {
        fprintf(stderr, "Error al abrir el archivo\n");
        return EXIT_FAILURE;
    }

    fwrite(personas, sizeof(persona_t), 10, f_personas_bin);

    fclose(f_personas_bin);

    // a) c)

    //---- a)
    f_personas_bin = fopen("personas.bin", "rb");
    if (f_personas_bin == NULL) {
        fprintf(stderr, "Error al abrir el archivo\n");
        return EXIT_FAILURE;
    }

    persona_t p;
    assert(leer_persona(f_personas_bin, &p));
    printf("Persona leida: %s %d %f\n", p.nombre, p.dni, p.altura);

    //---- c)
    persona_t personas_cpy[10];
    size_t n_personas;

    assert(leer_personas("personas.bin", personas_cpy, 10, &n_personas));
    printf("Personas leidas: %lu\n", n_personas);
    for (size_t i = 0; i < n_personas; i++)
        printf("Persona %lu: %s %d %f\n", i, personas_cpy[i].nombre, personas_cpy[i].dni, personas_cpy[i].altura);


    fclose(f_personas_bin);

    // b)
    FILE *f_personas_txt = fopen("personas.txt", "w");
    if (f_personas_txt == NULL) {
        fprintf(stderr, "Error al abrir el archivo\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 10; i++)
        escribir_persona(f_personas_txt, &personas[i]);

    fclose(f_personas_txt);

    return 0;
}

#elif N_EJERCICIO == 3

#define MAX 100

typedef struct {
    char nombre[MAX];
    unsigned int dni;
    float altura;
} persona_t;

void help_msg(void) {
    printf("\n");
    printf("Ejercicio 3\n");
    printf("\n");
    printf("Uso: ./main <archivo CSV [bin]>\n");
    printf("\n");
}

bool leer_persona(FILE *f, persona_t *p) {
    return fread(p, sizeof(persona_t), 1, f);
}

void escribir_persona(FILE *f, const persona_t *p) {
    fprintf(f, "%s,%u,%.2f", p->nombre, p->dni, p->altura);
}

bool leer_personas(const char *r, persona_t v[], size_t max, size_t *n) {

    *n = 0;

    FILE *f = fopen(r, "rb");
    if (f == NULL)
        return false;

    while ((*n) < max)
        if (!leer_persona(f, &v[(*n)++])){
            fclose(f);
            return false;
        }

    fclose(f);

    return true;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Error. Faltan cantidad de argumentos invalida. Uso: ./main <archivo CSV [bin]>\n");
        return EXIT_FAILURE;
    }

    FILE *f_personas_csv = fopen(argv[1], "r");
    if (f_personas_csv == NULL) {
        fprintf(stderr, "Error al abrir el archivo. Esto puede deberse a que los datos ingresados son incorrectos. Verifique y vuela a intentarlo.\n");
        return EXIT_FAILURE;
    }

    persona_t personas[10];
    size_t n_personas;

    assert(leer_personas(argv[1], personas, 10, &n_personas));
    printf("Personas leidas: %lu\n", n_personas);
    for (size_t i = 0; i < n_personas; i++)
        printf("Persona %lu: %s %d %f\n", i, personas[i].nombre, personas[i].dni, personas[i].altura);

    fclose(f_personas_csv);

    return 0;
}

#endif