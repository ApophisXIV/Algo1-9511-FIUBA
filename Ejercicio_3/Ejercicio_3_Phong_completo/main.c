
/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-10-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "main.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

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

vector_t vector_resta(const vector_t a, const vector_t b) {
    return (vector_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

vector_t vector_interpolar_recta(const vector_t o, const vector_t d, const float t) {
    return (vector_t){d.x * t + o.x, d.y * t + o.y, d.z * t + o.z};
}

void color_imprimir(const color_t c) {
	// //Si c es menor a 0 poner en 0
	// if (c.r < 0)
	// 	printf("CR es menor a 0\n");
	// if (c.g < 0)
	// 	printf("CG es menor a 0\n");
	// if (c.b < 0)
	// 	printf("CB es menor a 0\n");

    printf("%d ", (unsigned int)(c.r > 1 ? 255 : (c.r < 0 ? 0 : c.r * 255)));
    printf("%d ", (unsigned int)(c.g > 1 ? 255 : (c.g < 0 ? 0 : c.g * 255)));
    printf("%d ", (unsigned int)(c.b > 1 ? 255 : (c.b < 0 ? 0 : c.b * 255)));
}

color_t color_sumar(const color_t c, const color_t m, const float p) {
    return (color_t){c.r + p * m.r, c.g + p * m.g, c.b + p * m.b};
}

color_t color_absorber(const color_t b, const color_t c) {
    return (color_t){b.r * c.r, b.g * c.g, b.b * c.b};
}

esfera_t *esfera_crear(const vector_t centro, const float radio, const color_t color, const float ka, const float kd, const float ks, const float kr) {

    esfera_t *esfera_h = malloc(sizeof(esfera_t));
    if (esfera_h == NULL)
        return NULL;

    esfera_h->centro = centro;
    esfera_h->radio = radio;
    esfera_h->color = color;
    esfera_h->ka = ka;
    esfera_h->kd = kd;
    esfera_h->ks = ks;
    esfera_h->kr = kr;

    return esfera_h;
}

void esfera_destruir(esfera_t *esfera) {
    free(esfera);
}

luz_t *luz_crear(const vector_t posicion, const color_t color, const bool es_puntual) {

    luz_t *luz_h = malloc(sizeof(luz_t));
    if (luz_h == NULL)
        return NULL;

    luz_h->posicion = posicion;
    luz_h->color = color;
    luz_h->es_puntual = es_puntual;

    return luz_h;
}

void luz_destruir(luz_t *luz) {
    free(luz);
}

bool arreglo_agregar(arreglo_t *a, void *e) {

    void *arreglo_reescalado_aux = realloc(a->v, (a->n + 1) * sizeof(void *));

    if (arreglo_reescalado_aux == NULL)
        return false;

    a->v = arreglo_reescalado_aux;
    a->v[a->n++] = e;

    return true;
}

float esfera_distancia(const esfera_t *esfera, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal) {

    const vector_t co = vector_resta(esfera->centro, o);
    const float cd = vector_producto_interno(co, d);
    const float delta = cd * cd - vector_producto_interno(co, co) + esfera->radio * esfera->radio;

    if ((delta >= 0) && (cd + sqrt(delta) > 0)) {    // Corto circuito. Priorizo delta >= 0.

        const float sqrtDelta = sqrt(delta);
        const float t = cd - sqrtDelta > 0 ? cd - sqrtDelta : cd + sqrtDelta;

        if (punto != NULL && normal != NULL) {
            *punto = vector_interpolar_recta(o, d, t);
            *normal = vector_resta(*punto, esfera->centro);
            normal->x /= esfera->radio;
            normal->y /= esfera->radio;
            normal->z /= esfera->radio;
        }
        return t;
    }
    return INFINITO;
}

color_t computar_intensidad(const arreglo_t *esferas, const arreglo_t *luces, const color_t ambiente, const vector_t o, const vector_t d, size_t profundidad) {

    float t_min = INFINITO;
    size_t n_esfera_min_Z;
    vector_t p_min;
    vector_t n_min;

    for (size_t i = 0; i < esferas->n; i++) {

        vector_t p, n;
        const float t = esfera_distancia(esferas->v[i], o, d, &p, &n);

        if (t < t_min) {
            t_min = t;
            n_esfera_min_Z = i;
            p_min = p;
            n_min = n;
        }
    }

    if (t_min != INFINITO) {

        const esfera_t *e_prueba = esferas->v[n_esfera_min_Z];
        color_t c_difusa = SIN_APORTE;

        for (size_t k = 0; k < luces->n; k++) {

            const luz_t *l_prueba = luces->v[k];
            vector_t l_luz = l_prueba->posicion;

            if (l_prueba->es_puntual)
                l_luz = vector_normalizar(vector_resta(l_prueba->posicion, p_min));

            float t_luz = INFINITO;

            for (size_t j = 0; j < esferas->n; j++)
                if (n_esfera_min_Z != j) {
                    t_luz = esfera_distancia(esferas->v[j], p_min, l_luz, NULL, NULL);
                    if (t_luz != INFINITO)
                        break;
                }

            if (t_luz == INFINITO) {
                const color_t i_luz_cm = color_absorber(l_prueba->color, e_prueba->color);
                const float l_n = vector_producto_interno(l_luz, n_min);
                const float d_n = vector_producto_interno(d, n_min);
                const vector_t r = vector_resta(d,(vector_t){n_min.x * 2 * d_n, n_min.y * 2 * d_n, n_min.z * 2 * d_n});
                const float l_r = vector_producto_interno(l_luz,r);
                c_difusa = color_sumar(c_difusa, i_luz_cm, e_prueba->kd * (l_n < 0 ? 0 : l_n) + e_prueba->ks * pow((l_r < 0 ? 0 : l_r),10));
                // c_difusa = color_sumar(c_difusa, i_luz_cm, e_prueba->kd * (l_n < 0 ? 0 : l_n));
            }
        }
        color_t c = color_sumar(c_difusa, ambiente, e_prueba->ka);

        // Recursion
        if (profundidad > 0) {
            const vector_t r = vector_resta(d, (vector_t){n_min.x * 2 * vector_producto_interno(d, n_min), n_min.y * 2 * vector_producto_interno(d, n_min), n_min.z * 2 * vector_producto_interno(d, n_min)});
            // Offset del punto p_min
            const vector_t p_min_offset = (vector_t){p_min.x + r.x * 10E-6, p_min.y + r.y * 10E-6, p_min.z + r.z * 10E-6};
            const color_t c_reflejado = computar_intensidad(esferas, luces, ambiente, p_min_offset, r, profundidad - 1);
            c = color_sumar(c, c_reflejado, e_prueba->kr);
        }

        return c;
    }
    return NEGRO;
}

#define R_DEPTH 10

int main(void) {
    arreglo_t luces = {NULL, 0};
    arreglo_t esferas = {NULL, 0};

    color_t ambiente = {.05, .05, .05};

    assert(arreglo_agregar(&luces, luz_crear(vector_normalizar((vector_t){0, 1, 0}), (color_t){.2, .2, .2}, false)));
    assert(arreglo_agregar(&luces, luz_crear((vector_t){-2, 10, 2.5}, (color_t){.9, 0, 0}, true)));
    assert(arreglo_agregar(&luces, luz_crear((vector_t){2, 10, 2.5}, (color_t){0, .9, 0}, true)));
    assert(arreglo_agregar(&luces, luz_crear((vector_t){0, 10, 5}, (color_t){0, 0, .9}, true)));

    assert(luces.n == 4);
    for (size_t i = 0; i < luces.n; i++)
        assert(luces.v[i] != NULL);

    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){0, 1, 2.4}, .3, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){0, -.4, 3}, 1, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));

    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-2, -.6, 3}, .3, (color_t){1, 0, 0}, 1, .8, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-1.73, -.6, 2}, .3, (color_t){1, 1, 0}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-1, -.6, 1.26}, .3, (color_t){0, 1, 0}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){0, -.6, 1}, .3, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){1, -.6, 1.26}, .3, (color_t){0, 1, 1}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){1.73, -.6, 2}, .3, (color_t){0, 0, 1}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){2, -.6, 3}, .3, (color_t){1, 0, 1}, 1, 1, 0.6, .33)));

    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-3, 2.5, 4.3}, .3, (color_t){1, 1, 1}, 1, 0, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-2, 2.5, 4.3}, .3, (color_t){1, 1, 1}, 1, .16, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-1, 2.5, 4.3}, .3, (color_t){1, 1, 1}, 1, .33, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){0, 2.5, 4.3}, .3, (color_t){1, 1, 1}, 1, .5, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){1, 2.5, 4.3}, .3, (color_t){1, 1, 1}, 1, .66, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){2, 2.5, 4.3}, .3, (color_t){1, 1, 1}, 1, .83, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){3, 2.5, 4.3}, .3, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));

    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-3, 1.5, 4}, .3, (color_t){1, 1, 1}, 0, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-2, 1.5, 4}, .3, (color_t){1, 1, 1}, .16, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){-1, 1.5, 4}, .3, (color_t){1, 1, 1}, .33, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){0, 1.5, 4}, .3, (color_t){1, 1, 1}, .5, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){1, 1.5, 4}, .3, (color_t){1, 1, 1}, .66, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){2, 1.5, 4}, .3, (color_t){1, 1, 1}, .83, 1, 0.6, .33)));
    assert(arreglo_agregar(&esferas, esfera_crear((vector_t){3, 1.5, 4}, .3, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));

    assert(esferas.n == 23);
    for (size_t i = 0; i < esferas.n; i++)
        assert(esferas.v[i] != NULL);

    printf("P3\n");
    printf("%d %d\n", ANCHO, ALTO);
    printf("255\n");

    float vz = ANCHO / 2 / tan(FOV / 2 * PI / 180);

    for (int vy = ALTO / 2; vy > -ALTO / 2; vy--)
        for (int vx = -ANCHO / 2; vx < ANCHO / 2; vx++) {
            color_imprimir(computar_intensidad(&esferas, &luces, ambiente, (vector_t){0, 0, 0}, vector_normalizar((vector_t){vx, vy, vz}), R_DEPTH));
            putchar('\n');
        }

    for (size_t i = 0; i < esferas.n; i++)
        esfera_destruir(esferas.v[i]);
    free(esferas.v);

    for (size_t i = 0; i < luces.n; i++)
        luz_destruir(luces.v[i]);
    free(luces.v);

    return 0;
}