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
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_EJERCICIO 1

#if N_EJERCICIO == 1

/*
Una palabra puede tener múltiples sinónimos. Se quiere modelar un TDA sinónimos de
palabra que permita almacenar la palabra y sus sinónimos. Se pide:

    a.Declarar la estructura que encapsula el TDA. Explicar qué representacada miembro
    y documentar el invariante de representación.

    b.Implementar la primitivasize_t sinonimos_cantidad_sinonimos(constsinonimos_t *s);
    que devuelva la cantidad de sinónimos que tieneasociada la palabra.

    c.Implementar la primitivabool sinonimos_es_sinonimo(constsinonimos_t *sinonimos, const sinonimos_t *palabra);
    que diga si la palabra que representa palabra está contenida entre los sinónimos de sinonimos.
    Por ejemplo (palabra: sinónimos):

    Programar: Exponer, planificar, plantear, proyectar, sistematizar,esquematizar, bosquejar.

    Exponer: Explicar, explanar, manifestar, referir, plantear, formu-lar, afirmar, alegar, declarar, describir, razonar.

    Entonces sinonimos_es_sinonimo(programar, exponer) ->true y sinonimos_es_sinonimo(exponer, programar) -> false.
*/

// Invariante de representacion:
//   - El vector de punteros a cadena de sinonimos mide cantidad_sinonimos
//   - El vector de punteros a cadena de sinonimos no puede contener NULL
//   - El vector de punteros a cadena de sinonimos no puede contener una cadena vacia
//   - La palabra no puede ser nula
//   - La cantidad de sinonimos no puede ser negativa. Si no tiene sinonimos, la cantidad de sinonimos es 0.
//   - Todos los sinonimos de la palabra deben ser distintos.
//   - Los sinonimos de la palabra deben ser escritos en minusculas al igual que la palabra.

// Invariante:
// El vector de sinonimos mide cantidad_sinonimos.
// El vector "sinonimos", son los sinonimos de palabra
// Si n_sinonimos vale 0, sinonimos vale NULL.
// Todos los punteros apuntan a memoria valida
//

/*
Invariante de representacion:
- El vector de punteros a cadena de sinonimos mide cantidad_sinonimos
- Si n_sinonimos vale 0, sinonimos vale NULL.
- Todos los punteros apuntan a memoria valida
*/

typedef struct {
    char *palabra;                // Palabra. Puntero a cadena.
    char **sinonimos;             // Sinonimos. Puntero a vector de punteros a cadena
    size_t cantidad_sinonimos;    // Cantidad de sinonimos. Entero sin signo.
} sinonimos_t;

/**
 * @brief  Devuelve la cantidad de sinonimos que tiene asociada la palabra.
 * @pre    La estructura debe haber sido inicializada.
 * @param  *s: Puntero a la estructura sinonimos_t.
 * @retval La cantidad de sinonimos que tiene asociada la palabra.
 */
size_t sinonimos_cantidad_sinonimos(const sinonimos_t *s) {
    return s->cantidad_sinonimos;
}

/**
 * @brief  Verifica si una palabra es un sinonimo de otra
 * @pre    El sinonimos_t debe estar inicializado y no puede ser nulo
 * @pre    La palabra debe ser inicializada y no puede ser nula
 * @pre    La palabra debe ser escrita en minusculas
 * @post
 * @param  *sinonimos: Puntero al sinonimos_t
 * @param  *palabra: Puntero a la palabra
 * @retval true: Si la palabra es un sinonimo
 * @retval false: Si la palabra no es un sinonimo
 */
bool sinonimos_es_sinonimo(const sinonimos_t *sinonimos, const sinonimos_t *palabra) {
    for (size_t i = 0; i < sinonimos->cantidad_sinonimos; i++)
        if (strcmp(sinonimos->sinonimos[i], palabra->palabra) == 0)
            return true;
    return false;
}
// 6207841334
//

int main(void) {

    sinonimos_t s = {
        .palabra = "programar",
        .sinonimos = (char *[]){"exponer", "planificar", "plantear", "proyectar", "sistematizar", "esquematizar", "bosquejar"},
        .cantidad_sinonimos = 7};

    sinonimos_t s2 = {
        .palabra = "exponer",
        .sinonimos = (char *[]){"explicar", "explanar", "manifestar", "referir", "plantear", "formular", "afirmar", "alegar", "declarar", "describir", "razonar"},
        .cantidad_sinonimos = 11};

    printf("%s\n", sinonimos_es_sinonimo(&s, &s2) ? "true" : "false");
    printf("%s\n", sinonimos_es_sinonimo(&s2, &s) ? "true" : "false");

    return 0;
}

#elif N_EJERCICIO == 2

#define MAX_NOMBRE 100

typedef struct {
    unsigned int id;
    char nombre[MAX_NOMBRE];
    float precio;
} producto_t;

bool escribir_producto_csv(const producto_t *p, FILE *f) {
    return fprintf(f, "%d,%s,%.2f\n", p->id, p->nombre, p->precio) > 0;
}

bool leer_productos(const char *r, producto_t ps[], size_t max, size_t *n) {

    if (r == NULL || ps == NULL || max == 0 || n == NULL)
        return false;

    FILE *fr = fopen(r, "rb");
    if (fr == NULL)
        return false;

    *n = fread(ps, sizeof(producto_t), max, fr);

    fclose(fr);

    return true;
}

int main(void) {

    // Parte 1
    producto_t prods[8];

    prods[0] = (producto_t){.id = 1, .nombre = "Mate", .precio = 1.0};
    prods[1] = (producto_t){.id = 2, .nombre = "Cafe", .precio = 2.0};
    prods[2] = (producto_t){.id = 3, .nombre = "Harina", .precio = 3.0};
    prods[3] = (producto_t){.id = 4, .nombre = "Palmitos", .precio = 4.0};
    prods[4] = (producto_t){.id = 5, .nombre = "Yerba", .precio = 5.0};
    prods[5] = (producto_t){.id = 6, .nombre = "Mermelada", .precio = 6.0};
    prods[6] = (producto_t){.id = 7, .nombre = "Cacao", .precio = 7.0};
    prods[7] = (producto_t){.id = 8, .nombre = "Picadillo", .precio = 8.0};

    FILE *f = fopen("productos.csv", "w");
    if (f == NULL)
        return 1;

    for (size_t i = 0; i < 8; i++)
        assert(escribir_producto_csv(&prods[i], f));

    fclose(f);

    // Parte 2

    // Para leer en bin necesito un archivo .bin
    FILE *fw = fopen("productos.bin", "wb");
    if (fw == NULL)
        return 1;

    fwrite(prods, sizeof(producto_t), 8, fw);
    fclose(fw);

    size_t n_leidos = 0;

    producto_t prods_read[8];
    assert(leer_productos("productos.bin",prods_read,8, &n_leidos));

    printf("Se leyeron %zu productos\n", n_leidos);

    return 0;
}

#elif N_EJERCICIO == 3

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Error. Uso: ./convertir_productos [archivo_entrada] <[archivo_salida (opcional)]>\n");
        return 1;
    }

    FILE *f_entrada = fopen(argv[1], "rb");
    if (f_entrada == NULL) {
        fprintf(stderr, "Error al abrir el archivo %s\n", argv[1]);
        return 1;
    }

    return 0;
}

#endif