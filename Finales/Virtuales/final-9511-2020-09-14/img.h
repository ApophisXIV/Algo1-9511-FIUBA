#ifndef IMG_H
#define IMG_H

#include "rgba.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct img img_t;

img_t *img_crear(const size_t ancho, const size_t alto);
void img_destruir(img_t *img);

size_t img_ancho(const img_t *img);
size_t img_alto(const img_t *img);

void img_set_pixel(img_t *img, const size_t x, const size_t y, const rgba_t color);
rgba_t img_get_pixel(img_t *img, const size_t x, const size_t y);

img_t *img_clonar(const img_t *img);

bool img_escribir(const img_t *img, FILE *f);
img_t *img_leer(FILE *f);

void img_ordenar_por_tamagno(img_t *img[], const size_t n);

bool img_pintar(img_t *img, const rgba_t color);
bool img_sellar(img_t *img_papel, const img_t *img_sello, const int x, const int y);


img_t *img_crear_texto(const char *s, const rgba_t c_fondo, const rgba_t c_texto);


#endif
