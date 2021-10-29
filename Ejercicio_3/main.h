/**
 * @file main.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MAIN_H
#define MAIN_H

/* -------------------------------- Libraries ------------------------------- */

#include <stdio.h>
#include <float.h>
#include <stdbool.h>

/* -------------------------------- Constants ------------------------------- */

#define ANCHO 640
#define ALTO 480
#define FOV 90

#define PI 3.1415927f
#define INFINITO FLT_MAX

#define NEGRO (color_t){0, 0, 0}
#define SIN_APORTE NEGRO

/* ----------------------------- Data structures ---------------------------- */

typedef struct {
    float x, y, z;
} vector_t;

typedef struct {
    float r, g, b;
} color_t;

typedef struct {
    vector_t centro;
    float radio;

    color_t color;

    float ka, kd;
} esfera_t;

typedef struct {
    vector_t posicion;    // Si es_puntual es una coordenada, si no una dirección
    color_t color;
    bool es_puntual;
} luz_t;

typedef struct {
    void **v;
    size_t n;
} arreglo_t;

/* --------------------------------- Macros --------------------------------- */

#define DEG_TO_RAD(deg) (deg) * (PI / 180)

/* ------------------------------- Prototypes ------------------------------- */

/** @defgroup F1 Funciones auxiliares
 *  Lista de funciones utiles para el programa
 *  @{
 */

/**
 * @brief  Calcula el producto interno de los vectores provistos a partir de sus componentes individuales
 * @note   Los parametros que recibe son de tipo read-only
 * @param  a: Struct vector_t cuyo miembro es una terna ordenada A
 * @param  b: Struct vector_t cuyo miembro es una terna ordenada B
 * @retval P.Interno: Resultado del producto interno del vector a y b
 */
float vector_producto_interno(const vector_t a, const vector_t b);

/**
 * @brief  Calcula la norma del vector provisto a partir de sus componentes
 * @note   El parametro que recibe es de tipo read-only
 * @param  a: Struct vector_t cuyo miembro es una terna ordenada A
 * @retval Norma: Resultado de la norma del vector provisto
 */
float vector_norma(const vector_t a);

/**
 * @brief  Computa el versor asociado al vector provisto
 * @note   El resultado es almacenado en el mismo vector provisto que decayo en un puntero
 * @param  a: Struct vector_t cuyo miembro es una terna ordenada A
 * @retval Versor: Versor del vector provisto
 */
vector_t vector_normalizar(const vector_t a);

/**
 * @brief  Calcula la resta entre el vector a y b.
 * @note   El parametro a y b que recibe es de tipo read-only
 * @param  a: Struct vector_t cuyo miembro es una terna ordenada A
 * @param  b: Struct vector_t cuyo miembro es una terna ordenada B
 * @retval Resta: Resultado de la resta entre el vector a y b
 */
vector_t vector_resta(const vector_t a, const vector_t b);

/**
 * @brief  Calcula las coordenadas del punto en el que un determinado rayo impacto para una 
 *         distancia t desde un origen o
 * @note   O, d y t son del tipo read-only. El rayo d debe ser un versor
 * @param  o: Struct vector_t cuyo miembro es una terna ordenada. Coordenadas de origen desde las que el rayo es disparado
 * @param  d: Struct vector_t cuyo miembro es una terna ordenada. Versor asociado al rayo a disparar contra la esfera
 * @param  t: Distancia a la cual el rayo d impacto sobre el objetivo
 * @retval Punto: Coordenadas del punto en el que el rayo impacto para una distancia t desde un origen o
 */
vector_t vector_interpolar_recta(const vector_t o, const vector_t d, const float t);

/**
 * @brief  Imprime por stdout un color en formato RGB [0, 255]
 * @note   c es de tipo read-only y de rango [0, 1].
 * @param  c: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color 1
 * @retval None
 */
void color_imprimir(const color_t c);

/**
 * @brief  Computa la distancia a la que se encuentra desde un determinado origen el 
 *         primer impacto de un rayo sobre una esfera de radio r y centro c. Devuelve por interfaz
 *         el punto y normal de la esfera en el punto de impacto.
 * @note   esfera, o y d son del tipo read-only. El rayo d debe ser un versor. 
 *         El punto y normal son punteros a structs de tipo vector_t. Devueltos por interfaz
 * @param  *esfera: Puntero a struct esfera_t.
 * @param  o: Struct vector_t cuyo miembro es una terna ordenada. Coordenadas de origen desde las que el rayo es disparado
 * @param  d: Struct vector_t cuyo miembro es una terna ordenada. Versor asociado al rayo a disparar contra la esfera
 * @param  *punto: Puntero a struct vector_t de una terna ordenada. Punto de impacto.
 * @param  *normal: Puntero a struct vector_t de una terna ordenada. Normal de la esfera en el punto de impacto. 
 * @retval t: Distancia calculada
 * @retval INFINITO: El rayo no impacto sobre ninguna esfera
 */
float esfera_distancia(const esfera_t *esfera, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal);

/** @} */

/** @defgroup F2 Modelo de Phong
 *  Lista de funciones necesarias para implementar el modelo de Phong
 *  @{
 */

/**
 * @brief  Computa la suma de dos colores
 * @note   c, m y p son del tipo read-only.
 * @param  c: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color 1
 * @param  m: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color 2 a sumar
 * @param  p: Coeficiente que multiplica al color 2 antes de sumar
 * @retval Color: Resultado de la suma de los colores
 */
color_t color_sumar(const color_t c, const color_t m, const float p);

/**
 * @brief  Computa la absorcion de dos colores
 * @note   b y c son de tipo read-only.
 * @param  b: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color 1
 * @param  c: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color 2 a absorber
 * @retval Color: Resultado de la absorcion entre los colores
 */
color_t color_absorber(const color_t b, const color_t c);

/**
 * @brief  Computa la intensidad de luz sobre un determinado punto de impacto en formato RGB 
 *         [0,1] para un determinado rayo d disparado desde un origen O sobre n esferas 
 *         de centro C y radio R
 * @note   Los parametros que recibe la funcion son de tipo read-only.
 * @param  *esferas: Puntero a struct arreglo_t donde uno de sus miembros apunta a un arreglo de punteros
 *                  genericos que a su vez apuntan a structs esferas_t. Estas son las esferas presentes
 *                  en la escena
 * @param  *luces: Puntero a struct arreglo_t donde uno de sus miembros apunta a un arreglo de punteros
 *                genericos que a su vez apuntan a structs luces_t. Estas son las luces presentes 
 *                en la escena  
 * @param  ambiente: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color ambiente
 * @param  o: Struct vector_t cuyo miembro es una terna ordenada. Coordenadas de origen desde las que el rayo es disparado
 * @param  d: Struct vector_t cuyo miembro es una terna ordenada. Versor asociado al rayo a disparar contra la esfera
 * @retval C: Valor de intensidad de color calculado. Si no hay aporte de luz difusa este sera la luz ambiente
 * @retval NEGRO: Se devuelve negro (0,0,0) en caso de que el rayo no impacte contra ninguna esfera
 */
color_t computar_intensidad(const arreglo_t *esferas, const arreglo_t *luces, const color_t ambiente, const vector_t o, const vector_t d);

/** @} */

/** @defgroup F3 Memoria dinamica
 *  Lista de funciones necesarias para el manejo de memoria dinamica
 *  @{
 */

/**
 * @brief  Creacion de una estructura esfera_t en memoria dinamica
 * @note   Los parametros que recibe la funcion son de tipo read-only.
 * @param  centro: Struct vector_t cuyo miembro es una terna ordenada. Centro de la esfera
 * @param  radio: Radio de la esfera
 * @param  color: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color ambiente
 * @param  ka: Coeficiente de reflexion ambiental
 * @param  kd: Coeficiente de reflexion difusa
 * @retval P: Puntero a la estructura esfera_t creada
 * @retval NULL: Error en la creacion de la estructura
 */
esfera_t *esfera_crear(const vector_t centro, const float radio, const color_t color, const float ka, const float kd);

/**
 * @brief  Libera la memoria dinamica de una estructura esfera_t
 * @param  *esfera: Puntero a la estructura esfera_t a liberar
 * @retval None
 */
void esfera_destruir(esfera_t *esfera);

/**
 * @brief  Creacion de una estructura luz_t en memoria dinamica
 * @note   Los parametros que recibe la funcion son de tipo read-only.
 * @param  posicion: Struct vector_t cuyo miembro es una terna ordenada. Posicion de la luz
 * @param  color: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color de la luz
 * @param  es_puntual: Booleano que indica si la luz es puntual o no
 * @retval P: Puntero a la estructura luz_t creada
 * @retval NULL: Error en la creacion de la estructura
 */
luz_t *luz_crear(const vector_t posicion, const color_t color, const bool es_puntual);

/**
 * @brief  Libera la memoria dinamica de una estructura luz_t
 * @param  *luz: Puntero a la estructura luz_t a liberar
 * @retval None
 */
void luz_destruir(luz_t *luz);

/** @} */

#endif    // MAIN_H