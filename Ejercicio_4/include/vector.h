/**
 * @file vector.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

/** @addtogroup Shapes
 *  @{
 */

/** @defgroup Algebra Algebra
 *  Operaciones con vectores
 *  @{
 */

/* ----------------------------- Data structures ---------------------------- */
typedef struct {
    float x, y, z;
} vector_t;

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief   Calcula el producto interno de los vectores provistos a partir de sus componentes individuales
 * @param   a: Struct vector_t cuyo miembro es una terna ordenada A
 * @param   b: Struct vector_t cuyo miembro es una terna ordenada B
 * @retval  float: Resultado del producto interno del vector a y b
 */
float   vector_producto_interno(const vector_t a, const vector_t b);

/**
 * @brief   Calcula la norma del vector provisto a partir de sus componentes
 * @param   a: Struct vector_t cuyo miembro es una terna ordenada A
 * @retval  float: Resultado de la norma del vector provisto
 */
float   vector_norma(const vector_t a);

/**
 * @brief   Computa el versor asociado al vector provisto
 * @param   a: Struct vector_t cuyo miembro es una terna ordenada A
 * @retval  vector_: Versor del vector provisto
 */
vector_t    vector_normalizar(const vector_t a);

/**
 * @brief   Calcula las coordenadas del punto en el que un determinado rayo impacto para una
 *          distancia t desde un origen o
 * @pre     El rayo d debe ser un versor
 * @param   o: Struct vector_t cuyo miembro es una terna ordenada. Coordenadas de origen desde las que el rayo es disparado
 * @param   d: Struct vector_t cuyo miembro es una terna ordenada. Versor asociado al rayo a disparar al objetivo.
 * @param   t: Distancia a la cual el rayo d impacto sobre el objetivo
 * @retval  vector_t: Coordenadas del punto en el que el rayo impacto para una distancia t desde un origen o
 */
vector_t    vector_interpolar_recta(const vector_t o, const vector_t d, const float t);

/** @} */
/** @} */

#endif    // VECTOR_H