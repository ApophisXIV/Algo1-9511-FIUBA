#ifndef RGBA_H
#define RGBA_H

#include <stdint.h>

typedef uint8_t componente_t;
typedef uint32_t rgba_t;

rgba_t rgba(const componente_t r, const componente_t g, const componente_t b, const componente_t a);
componente_t rgba_r(const rgba_t rgba);
componente_t rgba_g(const rgba_t rgba);
componente_t rgba_b(const rgba_t rgba);
componente_t rgba_a(const rgba_t rgba);

#endif
