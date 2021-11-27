/**
 * @file vector.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <math.h>

#include "../../../include/vector.h"

float vector_producto_interno(const vector_t a, const vector_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vector_norma(const vector_t a) {
    return sqrt(vector_producto_interno(a, a));
}

vector_t vector_normalizar(const vector_t a) {
    const float n_aux = vector_norma(a);
    return (vector_t){a.x / n_aux, a.y / n_aux, a.z / n_aux};
}

vector_t vector_interpolar_recta(const vector_t o, const vector_t d, const float t) {
    return (vector_t){d.x * t + o.x, d.y * t + o.y, d.z * t + o.z};
}
