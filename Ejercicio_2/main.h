
/**
 * @file main.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-09-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MAIN_H
#define MAIN_H

/* -------------------------------- Libraries ------------------------------- */

#include <stdio.h>
#include <float.h>

/* -------------------------------- Constants ------------------------------- */

#define ANCHO 640
#define ALTO 480
#define FOV 90

#define PI 3.1415927f
#define INFINITO FLT_MAX

#define NEGRO 0
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

const float ORIGEN_OBSERVADOR[3] = {0, 0 ,0};

/* --------------------------------- Macros --------------------------------- */

#define DEG_TO_RAD(deg) (deg) * (PI / 180)

#define OBJ_QTY sizeof(centros) / sizeof(centros[0])

// ------ Para uso interno durante desarrollo. Ignorar ------
/// \cond DO_NOT_DOCUMENT

// #define DEBUG

#define LONG_H_LINE     printf( "-----------------------------------------"\
                                "-----------------------------------------"\
                                "-----------------------------------------"\
                                "----------------------------------\n");

#define DEBUG_TABLE     printf( "Rayo: (%1.2f, %1.2f, %1.2f) | "\
                                "T: %1.2f | "\
                                "P: (%1.2f %1.2f %1.2f) | "\
                                "C: (%1.2f %1.2f %1.2f) C_Sombra: (%1.2f %1.2f %1.2f) | "\
                                "i: %zu j: %zu | "\
                                "N: (%1.2f %1.2f %1.2f) | "\
                                "I: %i \n",\
                                d[0], d[1], d[2],\
                                t,\
                                puntoImpacto[0], puntoImpacto[1], puntoImpacto[2],\
                                cs[i][0], cs[i][1], cs[i][2],\
                                cs[j][0], cs[j][1], cs[j][2],\
                                i,j,\
                                normalImpacto[0], normalImpacto[1], normalImpacto[2],\
                                I > II ? II : (I < 0 ? IA : I)\
                                );

#define MISSED_RAY      printf("Rayo: (%1.2f, %1.2f, %1.2f) NO PEGA\n", d[0], d[1], d[2]);
/// \endcond


/* ------------------------------- Prototypes ------------------------------- */

/**
 * @brief  Calcula el producto interno de los vectores provistos a partir de sus componentes individuales
 * @note   Los parametros que recibe son de tipo read-only
 * @param  a[3]: Terna ordenada A
 * @param  b[3]: Terna ordenada B
 * @retval P.Interno: Resultado del producto interno del vector a y b
 */
float producto_interno(const float a[3], const float b[3]);

/**
 * @brief  Calcula la norma del vector provisto a partir de sus componentes
 * @note   El parametro que recibe es de tipo read-only
 * @param  a[3]: Terna ordenada
 * @retval Norma: Resultado de la norma del vector provisto
 */
float norma(const float a[3]);

/**
 * @brief  Computa el versor asociado al vector provisto
 * @note   El resultado es almacenado en el mismo vector provisto que decayo en un puntero
 * @param  a[3]: Terna ordenada
 * @retval None
 */
void normalizar(float a[3]);

/**
 * @brief  Calcula la resta entre el vector a y b. El resultado se almacena en r.
 * @note   El parametro a y b que recibe es de tipo read-only
 * @param  r[3]: Terna ordenada donde se almacenara el resultado
 * @param  a[3]: Terna ordenada A
 * @param  b[3]: Terna ordenada B
 * @retval None
 */
void resta(float r[3], const float a[3], const float b[3]);

/**
 * @brief  Computa la distancia a la que se encuentra desde un determinado origen el 
 *         primer impacto de un rayo sobre una esfera de radio r y centro c
 * @note   C, O y d son del tipo read-only. El rayo d debe ser un versor
 * @param  c[3]: Terna ordenada. Coordenadas del centro de la esfera
 * @param  r: Radio de la esfera
 * @param  o[3]: Terna ordenada. Coordenadas de origen desde las que el rayo es disparado
 * @param  d[3]: Terna ordenada. Versor asociado al rayo a disparar contra la esfera 
 *               de radio r y centro c
 * @retval t: Distancia calculada
 * @retval INFINITO: El rayo no impacto sobre ninguna esfera
 */
float distancia_esfera(const float c[3], float r, const float o[3], const float d[3]);

/**
 * @brief  Computa un versor asociado a un vector normal en una esfera dado por un punto 
 *         p y su centro
 * @note   C y p son del tipo read-only. El resultado es un versor
 * @param  normal[3]: Terna ordenada donde se almacenara el resultado del versor 
 *                    asociado a la normal
 * @param  c[3]: Terna ordenada. Coordenadas del centro de la esfera
 * @param  r: Radio de la esfera
 * @param  p[3]: Terna ordenada. Coordenadas del punto de la esfera con el que sera 
 *               calculada la normal
 * @retval None
 */
void normal_esfera(float normal[3], const float c[3], float r, const float p[3]);

/**
 * @brief  Calcula las coordenadas del punto en el que un determinado rayo impacto para una 
 *         distancia t desde un origen o
 * @note   O y d son del tipo read-only. El rayo d debe ser un versor
 * @param  p[3]: Terna ordenada donde se almacenaran las coordenadas del punto calculadas
 * @param  o[3]: Terna ordenada. Coordenadas de origen desde las que el rayo es disparado
 * @param  d[3]: Terna ordenada. Versor asociado al rayo a disparar contra la esfera
 * @param  t: Distancia a la cual el rayo d impacto sobre el objetivo
 * @retval None
 */
void interpolar_recta(float p[3], const float o[3], const float d[3], float t);

/**
 * @brief  Computa la intensidad de luz en una escala de grises [0 - 255] para un 
 *         determinado rayo d disparado desde un origen O sobre n esferas de centro C y radio R
 * @note   
 * @param  cs[][3]: Array de ternas ordenadas con las coordenadas del centro de las esferas
 * @param  rs[]: Array con los radios de las esferas
 * @param  n_esferas: Cantidad de esferas
 * @param  luz[3]: Terna ordenada. Versor asociado al rayo de luz de la escena
 * @param  o[3]: Terna ordenada. Cordenadas de origen del observador
 * @param  d[3]: Terna ordenada. Versor asociado al rayo a disparar contra las esferas
 * @retval I: Valor de intensidad calculado
 * @retval IA: (Luz ambiente) 5 en el caso de que el valor calculado sea menor que 0 o alguna esfera
 *             proyecte su sombra sobre otra.
 * @retval II: (Intensidad maxima) El valor calculado sobrepasa el limite de 255 por lo que se devuelve 255
 * @retval NEGRO: Se devuelve negro (0) en caso de que el rayo no impacte contra ninguna esfera
 */
int computar_intensidad(const float cs[][3], const float rs[], size_t n_esferas, const float luz[3], const float o[3], const float d[3]);

/**
 * @brief  Generador de imagen primitiva
 * @note   Esta funcion se encarga del proceso de generacion de una escena de ancho 
 *         y alto definido para una determinada coordenada origen
 * @param  o[3]: Terna ordenada. Cordenadas de origen del observador
 * @param  _ANCHO: Ancho en pixeles de la escena
 * @param  _ALTO: Alto en pixeles de la escena
 * @param  _FOV: Campo de vision del observador
 * @retval None
 */
void generarImagen(const float o[3], unsigned int _ANCHO, unsigned int _ALTO, unsigned int _FOV);

#endif    // MAIN_H