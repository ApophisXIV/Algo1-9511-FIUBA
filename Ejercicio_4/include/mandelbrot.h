/**
 * @file madelbrot.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef MANDELBROT_H
#define MANDELBROT_H

/* -------------------------------- Includes -------------------------------- */
#include "color.h"
#include "vector.h"

/** @addtogroup Shapes
 *  @{
 */

/** @defgroup Mandelbrot Mandelbrot
 *  Generacion de fractales de Mandelbrot
 *  @{
 */

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief   Genera un fractal de Mandelbrot.
 * @pre     d debe ser un versor.
 * @param   ambiente: Color ambiente.
 * @param   o: Punto de origen del fractal.
 * @param   d: Direccion del rayo.
 * @retval  color_t: Color generado.
 */
color_t mandelbrot(color_t ambiente, vector_t o, vector_t d);

/** @} */
/** @} */

#endif    // MANDELBROT_H