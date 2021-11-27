/**
 * @file mandelbrot.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <math.h>

#include "../../../include/mandelbrot.h"

#define MAX_ITER 80

color_t mandelbrot(color_t ambiente, vector_t o, vector_t d) {

    vector_t c = (vector_t){(d.x / d.z) * 1.5 - .5, (d.y / d.z) * 1.5 + .1, 0};
    vector_t z = {0, 0, 0};
    int n = 0;
    while (vector_norma(z) <= 2 && n < MAX_ITER) {
        z = (vector_t){z.x * z.x - z.y * z.y, z.x * z.y + z.x * z.y, 0};
        z = vector_interpolar_recta(z, c, 1);
        n++;
    }

    if (n == MAX_ITER)
        return ambiente;

    float h = (n + 1 - log(log2(vector_norma(z)))) / MAX_ITER * 360;
    float x = (1 - fabs(fmodf(h / 60.0, 2) - 1));
    float r = 0, g = 0, b = 0;

    if (h < 60)
        r = 1, g = x;
    else if (h < 120)
        g = 1, r = x;
    else if (h < 180)
        g = 1, b = x;
    else if (h < 240)
        b = 1, g = x;
    else if (h < 300)
        b = 1, r = x;
    else
        r = 1, b = x;

    return (color_t){r, g, b};
}
