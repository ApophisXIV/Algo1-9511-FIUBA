#ifndef UNICODE_H
#define UNICODE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint32_t uchar_t;

size_t unicode_longitud(const uchar_t *s);
int unicode_comparar(const uchar_t *s1, const uchar_t *s2);

void unicode_concatenar(uchar_t *dst, const uchar_t *src);
void unicode_insertar(uchar_t *dst, int desde, const uchar_t *src);

void unicode_decodificar_utf8(uchar_t *dst, const uint8_t *src);
void unicode_codificar_utf8(const uchar_t *src, uint8_t *dst);

uchar_t *unicode_leer_archivo_utf8(const char *nombre_archivo);
bool unicode_escribir_archivo_utf8(const uchar_t *s, const char *nombre_archivo);

#endif
