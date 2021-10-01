
/**
 * @file main.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/* -------------------------------- Libraries ------------------------------- */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* -------------------------------- Constants ------------------------------- */

#define CX 0.5
#define CY 0.75
#define CZ 1.9
#define R  0.8

#define ANCHO 640
#define ALTO  480
#define FOV   90

#define PI 3.1415927f

/* --------------------------------- Macros --------------------------------- */

#define DEG_TO_RAD(deg) (deg) * (PI / 180)

/* ------------------------------- Prototypes ------------------------------- */

float producto_interno(float x1, float y1, float z1, float x2, float y2, float z2);

float norma(float x, float y, float z);

bool intersecta_esfera(float dx, float dy, float dz, float ox, float oy, float oz, float cx, float cy, float cz, float radius);

void generarImagen(float ox, float oy, float oz, unsigned int _ANCHO, unsigned int _ALTO, unsigned int _FOV);

#endif    // __MAIN_H__