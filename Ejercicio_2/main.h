
/**
 * @file main.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-09-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/* -------------------------------- Libraries ------------------------------- */

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/* -------------------------------- Constants ------------------------------- */

#define ANCHO 640
#define ALTO 480
#define FOV 90

#define PI 3.1415927
#define INFINITO FLT_MAX

#define IA 5
#define II 255

const float luz[3] = {0.2873478855663454, 0.9578262852211513, 0};

const float centros[][3] = {

    {-.4, .75, 1.55},
    {-.55, -.4, 2},
    {3, 1.5, 4},
    {3, 1.5, 5},
    {3, -1.5, 4},
    {3, -1.5, 5},
};

const float radios[] = {

    .3,
    .85,
    .4,
    .4,
    .4,
    .4,
};

/* --------------------------------- Macros --------------------------------- */

#define DEG_TO_RAD(deg) deg *(PI / 180)

#define ROWS_QTY sizeof(centros) / sizeof(centros[0])

/* ------------------------------- Prototypes ------------------------------- */

float distancia_esfera(const float c[3], float r, const float o[3], const float d[3]);
void normal_esfera(float normal[3], const float c[3], float r, const float p[3]);
int computar_intensidad(const float cs[][3], const float rs[], size_t n_esferas, const float luz[3], const float o[3], const float d[3]);
float producto_interno(const float a[3], const float b[3]);
float norma(const float a[3]);
void normalizar(float a[3]);
void resta(float r[3], const float a[3], const float b[3]);
void interpolar_recta(float p[3], const float o[3], const float d[3], float t);
void generarImagen(const float o[3], unsigned int _ANCHO, unsigned int _ALTO, unsigned int _FOV);

#endif    // __MAIN_H__