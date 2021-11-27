/**
 * @file imagen.c
 * @author Sebastián Santisi
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../../../include/imagen.h"

#include <stdlib.h>

struct imagen {
    color_t **lienzo;
    size_t ancho, alto;
};

imagen_t *imagen_crear(size_t ancho, size_t alto) {
    imagen_t *im = malloc(sizeof(imagen_t));
    if(im == NULL) return NULL;

    im->lienzo = malloc(alto * sizeof(color_t *));
    if(im->lienzo == NULL) {
        free(im);
        return NULL;
    }

    for(size_t i = 0; i < alto; i++) {
        im->lienzo[i] = malloc(ancho * sizeof(color_t));
        if(im->lienzo[i] == NULL) {
            imagen_destruir(im);
            return NULL;
        }
    }

    im->ancho = ancho;
    im->alto = alto;

    return im;
}

void imagen_destruir(imagen_t *im) {
    for(size_t i = 0; i < im->alto; i++)
        free(im->lienzo[i]);
    free(im->lienzo);
    free(im);
}

void imagen_dimensiones(const imagen_t *im, size_t *ancho, size_t *alto) {
    *ancho = im->ancho;
    *alto = im->alto;
}

bool imagen_set_pixel(imagen_t *im, size_t x, size_t y, color_t color) {
    if(x >= im->ancho || y >= im->alto)
        return false;

    im->lienzo[y][x] = color;
    return true;
}

color_t imagen_get_pixel(const imagen_t *im, size_t x, size_t y) {
    return im->lienzo[y][x];
}