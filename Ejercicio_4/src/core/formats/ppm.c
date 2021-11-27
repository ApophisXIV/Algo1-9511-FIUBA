/**
 * @file ppm.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stddef.h>
#include <stdint.h>

#include "../../../include/ppm.h"

static void f_color_imprimir(const color_t c, FILE *f) {
    fprintf(f, "%d ", (uint8_t)(c.r > 1 ? 255 : (c.r * 255)));
    fprintf(f, "%d ", (uint8_t)(c.g > 1 ? 255 : (c.g * 255)));
    fprintf(f, "%d ", (uint8_t)(c.b > 1 ? 255 : (c.b * 255)));
    fputc('\n', f);
}

void escribir_PPM(const imagen_t *imagen, FILE *f) {

    size_t ancho, alto;
    imagen_dimensiones(imagen, &ancho, &alto);

    fprintf(f, "P3\n%zd %zd\n255\n", ancho, alto);

    for (size_t y = alto; y > 0; y--)
        for (size_t x = 0; x < ancho; x++)
            f_color_imprimir(imagen_get_pixel(imagen, x, y - 1), f);
}